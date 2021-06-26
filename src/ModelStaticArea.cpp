#include "ModelStaticArea.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Partition_traits_2.h>
#include <CGAL/partition_2.h>
#include <CGAL/property_map.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>

#include "shader.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Partition_traits_2<K, CGAL::Pointer_property_map<K::Point_2>::type> Partition_traits_2;
typedef Partition_traits_2::Point_2 Point_2;
typedef Partition_traits_2::Polygon_2 Polygon_2;  // a polygon of indices
typedef std::list<Polygon_2> Polygon_list;

ModelStaticArea::ModelStaticArea(std::vector<glm::vec2> coords) : ModelStatic() {
    this->coords = coords;

    this->walls = false;
    this->minHeight = 0.0f;
    this->maxHeight = 0.0f;
}

void ModelStaticArea::createCoords() {
    if (walls) {  //ściany tylko wtedy gdy maja być

        enum coordEnum {
            leftDown,
            rightDown,
            rightUp,
            leftUp
        };

        for (uint i = 0; i < this->coords.size() - 1; i++) {
            float dist = glm::distance(coords.data()[i], coords.data()[i + 1]);

            std::vector<glm::vec2> textureSpace = {
                //TODO: have fun with texture coords
                glm::vec2(0.0f, this->minHeight / 4),
                glm::vec2(std::max((int)(dist / 4), 1), this->minHeight / 4),
                glm::vec2(std::max((int)(dist / 4), 1), this->maxHeight / 4),
                glm::vec2(0.0f, this->maxHeight / 4),
            };

            std::vector<glm::vec4> vertexSpace = {
                glm::vec4(coords.data()[i].x, minHeight, coords.data()[i].y, 1),
                glm::vec4(coords.data()[i + 1].x, minHeight, coords.data()[i + 1].y, 1),
                glm::vec4(coords.data()[i + 1].x, maxHeight, coords.data()[i + 1].y, 1),
                glm::vec4(coords.data()[i].x, maxHeight, coords.data()[i].y, 1),
            };

            this->verts.push_back(vertexSpace[leftDown]);  //jeden trójkąt
            this->verts.push_back(vertexSpace[leftUp]);
            this->verts.push_back(vertexSpace[rightUp]);

            this->textureCoords.push_back(textureSpace[leftDown]);
            this->textureCoords.push_back(textureSpace[leftUp]);
            this->textureCoords.push_back(textureSpace[rightUp]);

            this->verts.push_back(vertexSpace[rightDown]);  //drugi trójkąt
            this->verts.push_back(vertexSpace[leftDown]);
            this->verts.push_back(vertexSpace[rightUp]);

            this->textureCoords.push_back(textureSpace[rightDown]);
            this->textureCoords.push_back(textureSpace[leftDown]);
            this->textureCoords.push_back(textureSpace[rightUp]);
        }
    }

    // printf("created coords\n");

    //sufit
    try {
        auto a = this->divideIntoConvex(coords, 1);
        for (auto i : a)
            this->createCoordsPlanar(i);
    } catch (const std::exception& e) {
        //if error try in reverse direction
        try {
            auto a = this->divideIntoConvex(coords, 0);
            for (auto i : a)
                this->createCoordsPlanar(i);
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
            std::cerr << this->coords.data()[0].x << " " << this->coords.data()[0].y << std::endl
                      << std::endl;
        }
    }

    //TODO: podłoga???
}

void ModelStaticArea::createCoordsPlanar(std::vector<glm::vec2> data) {
    // function to create coords for drawing convex polygons (manually dividing into fan)
    glm::vec4 start = glm::vec4(data.data()[0].x, maxHeight, data.data()[0].y, 1);
    for (uint i = 1; i < data.size() - 1; i++) {
        glm::vec4 a, b;
        a = glm::vec4(data.data()[i].x, maxHeight, data.data()[i].y, 1);
        b = glm::vec4(data.data()[i + 1].x, maxHeight, data.data()[i + 1].y, 1);

        this->verts.push_back(start);
        this->verts.push_back(a);
        this->verts.push_back(b);

        this->textureCoords.push_back(glm::vec2(start.x, start.z));
        this->textureCoords.push_back(glm::vec2(a.x, a.z));
        this->textureCoords.push_back(glm::vec2(b.x, b.z));
    }
}

std::vector<std::vector<glm::vec2>> ModelStaticArea::divideIntoConvex(std::vector<glm::vec2> coords, bool dir) {
    // function to divide concave polygons into convex (no angles greater than 180 deg)
    std::vector<K::Point_2> points;
    for (auto i : coords) {
        points.push_back(K::Point_2(i.x, i.y));
    }
    Partition_traits_2 traits(CGAL::make_property_map(points));
    Polygon_2 polygon;
    if (dir == 1)
        for (uint i = 0; i < points.size() - 1; i++)
            polygon.push_back(i);
    else
        for (int i = points.size() - 1; i > 0; i--)
            polygon.push_back(i);
    Polygon_list partition_polys;
    CGAL::approx_convex_partition_2(polygon.vertices_begin(),
                                    polygon.vertices_end(),
                                    std::back_inserter(partition_polys),
                                    traits);
    std::vector<std::vector<glm::vec2>> ret;
    for (const Polygon_2& poly : partition_polys) {
        std::vector<glm::vec2> tmp;
        for (Point_2 p : poly.container()) {
            tmp.push_back(glm::vec2(points[p].x(), points[p].y()));
        }
        ret.push_back(tmp);
    }
    return ret;
}

void ModelStaticArea::addHeight(float min, float max) {
    this->maxHeight = max;
    this->minHeight = min;
}

void ModelStaticArea::addWalls() {
    this->walls = true;
}

void ModelStaticArea::draw(glm::mat4 M) {
    // M = glm::translate(M, glm::vec3(this->locationX, 0, this->locationY));
    // M = glm::rotate(M, this->direction * PI / 180, glm::vec3(0.0f, 1.0f, 0.0f));  //Pomnóż macierz modelu razy macierz obrotu o kąt angle wokół osi Y

    glUniformMatrix4fv(spColored->u("M"), 1, false, glm::value_ptr(M));  //ładowanie macierzy modelu

    glEnableVertexAttribArray(spColored->a("vertex"));
    glVertexAttribPointer(spColored->a("vertex"), 4, GL_FLOAT, false, 0, this->verts.data());

    glEnableVertexAttribArray(spColored->a("texCoord"));
    glVertexAttribPointer(spColored->a("texCoord"), 2, GL_FLOAT, false, 0, this->textureCoords.data());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->tex);
    glUniform1i(spColored->u("tex"), 0);

    glDrawArrays(GL_TRIANGLES, 0, this->verts.size());

    glDisableVertexAttribArray(spColored->a("vertex"));
    glDisableVertexAttribArray(spColored->a("texCoord"));
}