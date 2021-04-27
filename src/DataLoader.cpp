#include "DataLoader.h"

DataLoader::DataLoader() {
}

DataLoader::~DataLoader() {
}

std::vector<object_data> DataLoader::load_file(std::string filename,int debug)
{
    //TODO harden and error file opening (eg file not existing)
    std::fstream file;
    file.open(filename,std::ios::in);
    std::string line;
    std::vector<object_data> data;
    object_data* current_object=nullptr;
    using namespace std;
    while(getline(file,line))
    {
        if(line=="BEGIN")
        {
            if(debug) cout<<"Begin an object"<<endl;
            current_object = new object_data;
            data.push_back(*current_object);
        }
        else if(line=="PROP")
        {
            getline(file,line);
            if(debug) cout<<"Prop count: "<<line<<endl;
            int cnt = stoi(line);
            for(auto i=0;i<cnt;i++)
            {
                getline(file,line);
                stringstream ss;
                ss<<line;
                string a,b;
                ss>>a>>b;
                current_object->props.push_back(pair<string,string>(a,b));
                if(debug) cout<<a<<'\t'<<b<<endl;
            }
        }
        else if(line=="COORDS")
        {
            getline(file,line);
            if(debug) cout<<"Coord count: "<<line<<endl;
            int cnt = stoi(line);
            for(auto i=0;i<cnt;i++)
            {
                getline(file,line);
                stringstream ss;
                ss<<line;
                double a,b;
                ss>>a>>b;
                current_object->coords.push_back(glm::vec2(a,b));
                if(debug) cout<<a<<'\t'<<b<<endl;
            }
        }
        else if (line=="END")
        {
            if(debug) cout<<line<<endl;
            if(debug) for(auto i : current_object->props)
                cout<<i.first<<" "<<i.second<<endl;
        }
    }
    return data;
}