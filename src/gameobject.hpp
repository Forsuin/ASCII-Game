#pragma once

class GameObject {
   public:
    virtual void start() {};
    virtual void update() {};

    virtual ~GameObject() = default;
};
