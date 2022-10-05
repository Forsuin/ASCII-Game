#pragma once

#include <optional>
#include <utility>
#include <vector>
#include <unordered_map>

#include "entity.hpp"
#include "material.hpp"

//TODO: actually make Features/Buildables
//struct Feature{};
//
//TODO: actually make Items
//struct Item{};

class Tile : GameObject{
    //std::optional<Feature> feature;
    //std::vector<Item> items;
    Entity* entity;
    //Fluid
    Material material;
   public:

   public:
    Tile() : entity(nullptr), material(Material::STONE){}
    explicit Tile(const Material& material) : entity(nullptr), material(material) {}

    void setEntity(Entity* newEntity){
        entity = newEntity;
    }

    void removeEntity(){
        entity = nullptr;
    }

    Entity* getEntity(){
        return entity;
    }

//    void setMaterial(const Material newMaterial){
//        material = newMaterial;
//    }

    [[nodiscard]] Material getMaterial() const{
        return material;
    }

//    bool containsEntity() const;
//
//    void addFeature(Feature feature);
//    void removeFeature(Feature feature);
//    Feature getFeature() const;
//
//    void addItem(Item item);
//    void removeItem(Item item);

};