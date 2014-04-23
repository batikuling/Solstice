#ifndef SOL_RESOURCE_HOLDER_HPP
#define SOL_RESOURCE_HOLDER_HPP


#include <map>
#include <string>
#include <fstream>
#include <memory>
#include <stdexcept>


namespace sol{


template <typename Identifier, typename Resource>
class ResourceHolder{
public:

    void load(Identifier id, const std::string& path);

    template <typename SecondParameter>
    void load(Identifier id, const std::string& path, const SecondParameter& second_param);

    Resource& get(Identifier id);

private:
    std::map<Identifier, std::unique_ptr<Resource>> _resources;
}; // end class ResourceHolder


template <typename Identifier, typename Resource>
void ResourceHolder<Identifier, Resource>::load(Identifier id, const std::string& path){
    std::unique_ptr<Resource> resource(new Resource());
    if (not resource->loadFromFile(path))
        throw std::runtime_error("ResourceHolder::load() cannot load: " + path);

    //_resources.insert(std::make_pair(id, std::move(resource)));
    _resources[id] = std::move(resource);
}

template <typename Identifier, typename Resource>
template <typename SecondParameter>
void ResourceHolder<Identifier, Resource>::load(Identifier id, const std::string& path, const SecondParameter& second_param){
    std::unique_ptr<Resource> resource(new Resource());
    if (not resource->loadFromFile(path, second_param))
        throw std::runtime_error("ResourceHolder::load() cannot load: " + path);

    _resources.insert(std::make_pair(id, std::move(resource)));
}

template <typename Identifier, typename Resource>
Resource& ResourceHolder<Identifier, Resource>::get(Identifier id){
    if (not _resources.count(id))
        throw std::runtime_error("ResourceHolder::load() was called with a nonexistent ID.");
    return *_resources.at(id);
}






template <typename Identifier>
class ResourceHolder<Identifier, std::fstream>{
public:

    void load(Identifier id, const std::string& path);
    std::fstream& get(Identifier id);

private:

    std::map<Identifier, std::unique_ptr<std::fstream>> _resources;
}; // end class ResourceHolder


template <typename Identifier>
void ResourceHolder<Identifier, std::fstream>::load(Identifier id, const std::string& path){
    std::unique_ptr<std::fstream> file(new std::fstream(path));
    if (not *file)
        throw std::runtime_error("ResourceHolder<Identifier, fstream>::load() cannot load: " + path);

    _resources[id] = std::move(file);
}

template <typename Identifier>
std::fstream& ResourceHolder<Identifier, std::fstream>::get(Identifier id){
    if (not _resources.count(id))
        throw std::runtime_error("ResourceHolder::load() was called with a nonexistent ID.");
    return *_resources.at(id);
}




} // end namespace sol


#endif // SOL_RESOURCE_HOLDER_HPP
