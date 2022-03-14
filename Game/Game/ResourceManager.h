#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "FileMissingException.h"

template <typename Derived, class T>

/** ResourceManager class */
class ResourceManager
{
public:
    /*constructor for ResourceManager*/
    ResourceManager(const std::string& fileName)
    {
            ReadFile(fileName); //read our .txt file, allocate rsrcs
    }

    /**The function is searching for resource and adds it 
    @param resourceName name of the resource
    */
    bool AddResource(const std::string& resourceName)
    {
        auto res = Find(resourceName); //see if rsr is already allocated

        if (res) //if so
        {
            ++res->second;  //increments counter in resourceMap
            return true;
        }

        auto filePath = fileMap.find(resourceName);//find file path
        if (filePath == fileMap.end())  // if it's a valid file path
            return false;

        T* resource = Load(filePath->second);
        if (!resource)      //if resource doesn't load
            return false;

        // we place resource on our container keeping track of allocatoin of memory.
        resourceMap.emplace(resourceName, std::make_pair(resource, 1));

        return true;
    }

    /**The function return any datatype we passed
    @param resourceName name of the resource
    */
    T* GetResource(const std::string& resourceName)
    {
        auto res = Find(resourceName); 

        if (res)
            return res->first;
        else
            throw FileMissingException();
    }

    /**Any datatype we passed, we use its load function
    @param path refernece to a path
    */
    T* Load(const std::string& path)
    {
        return static_cast<Derived*>(this)->Load(path);
    }

    /*destructor for ResourceManager*/
    ~ResourceManager()
    {
        while (resourceMap.begin() != resourceMap.end())
        {
            delete resourceMap.begin()->second.first;
            resourceMap.erase(resourceMap.begin());
        }
    }


private:

    std::unordered_map< std::string, std::pair<T*, int> > resourceMap; //string with pair of a Resource type + counter

    std::unordered_map<std::string, std::string> fileMap;   //stores all resources at intialization of instance

    /**The function returns the correct pair
    @param resourceName reference to the name of the resource
    */
    std::pair<T*, int>* Find(const std::string& resourceName)
    {
        auto itr = resourceMap.find(resourceName);

        if (itr != resourceMap.end())
            return &itr->second;
        else
            return NULL;
    }

    /**The function is reading file and inserts pathname and path in a map
    @param resourceName reference to the name of the resource
    */
    void ReadFile(const std::string& fileName)
    {
        std::ifstream paths(fileName);

        if (paths.is_open())
        {
            std::string pathName;
            std::string path;

            while (!paths.eof())
            {
                paths >> pathName >> path;
                fileMap.emplace(pathName, path);

            }

            paths.close();
            return;

        }
        throw FileMissingException();
        std::cerr << "Fail" << std::endl;
    }
};
