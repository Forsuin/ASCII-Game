#pragma once

#include <initializer_list>
#include <random>
#include <string>
#include <unordered_map>
#include <algorithm>

#include "component.hpp"
#include "gameobject.hpp"


struct Entity : GameObject {
   private:
    std::unordered_map<std::string, std::unique_ptr<Component>> components;

   public:
    [[nodiscard]] bool hasComponent(const std::string& componentName) const{
        if(components.find(componentName) == components.end()){
            return false;
        }
        return true;
    }

    [[nodiscard]] bool hasComponents(std::initializer_list<std::string> names) const{
        if(components.empty()) return false;

        if(!std::ranges::all_of(names.begin(), names.end(), [&](const std::string& name){
                return hasComponent(name);
            })){

        }
        return true;
    }

    void addComponent(const std::string& name, std::unique_ptr<Component> component){
        components.insert({name, std::move(component)});
    }

    void addComponents(std::unordered_map<std::string, std::unique_ptr<Component>> newComponents){
        for(auto& i : newComponents){
            addComponent(i.first, std::move(i.second));
        }
    }

    void removeComponent(const std::string& name){
        components.erase(name);
    }

    void removeComponents(std::initializer_list<std::string> componentNames){
        for(const auto& name : componentNames){
            components.erase(name);
        }
    }

    template<typename T>
    std::optional<T*> getComponent(const std::string& name) const {
        if(components.contains(name)){
            return dynamic_cast<T*>(components.at(name).get());
        }
        else {
            return std::nullopt;
        }
    }
};
