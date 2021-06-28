#include "ModelStaticPlanar.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Partition_traits_2.h>
#include <CGAL/partition_2.h>
#include <CGAL/property_map.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Partition_traits_2<K, CGAL::Pointer_property_map<K::Point_2>::type> Partition_traits_2;
typedef Partition_traits_2::Point_2 Point_2;
typedef Partition_traits_2::Polygon_2 Polygon_2;  // a polygon of indices
typedef std::list<Polygon_2> Polygon_list;

ModelStaticPlanar::ModelStaticPlanar(std::vector<glm::vec2> data, float height, bool dir) {
    this->coords = data;
    this->height = height;
    this->dir = dir;

    this->createCoords();
}

ModelStaticPlanar::ModelStaticPlanar(std::vector<glm::vec2> data, float height)
    : ModelStaticPlanar(data, height, 1) {}

ModelStaticPlanar::~ModelStaticPlanar() {
}

void ModelStaticPlanar::createCoords() {
    try {
        auto a = this->divideIntoConvex(coords, 1);
        for (auto i : a) this->createCoordsPlanar(i);
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
    float len = 2 * dir - 1;  //this maps 0 to -1 and 1 to 1
    for (uint i = 0; i < verts.size(); i++) {
        normals.push_back(glm::vec4(0, len, 0, 0));
    }
}

void ModelStaticPlanar::createCoordsPlanar(std::vector<glm::vec2> data) {
    // function to create coords for drawing convex polygons (manually dividing into fan)
    glm::vec4 start = glm::vec4(data.data()[0].x, this->height, data.data()[0].y, 1);
    for (uint i = 1; i < data.size() - 1; i++) {
        glm::vec4 a, b;
        a = glm::vec4(data.data()[i].x, this->height, data.data()[i].y, 1);
        b = glm::vec4(data.data()[i + 1].x, this->height, data.data()[i + 1].y, 1);

        this->verts.push_back(start);
        this->verts.push_back(a);
        this->verts.push_back(b);

        this->textureCoords.push_back(glm::vec2(start.x, start.z));
        this->textureCoords.push_back(glm::vec2(a.x, a.z));
        this->textureCoords.push_back(glm::vec2(b.x, b.z));
    }
}

std::vector<std::vector<glm::vec2>> ModelStaticPlanar::divideIntoConvex(std::vector<glm::vec2> coords, bool dir) {
    // function to divide concave polygons into convex (no angles greater than 180 deg)
    std::vector<K::Point_2> points;
    for (auto i : this->coords) {
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

void ModelStaticPlanar::draw(glm::mat4 M) {
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