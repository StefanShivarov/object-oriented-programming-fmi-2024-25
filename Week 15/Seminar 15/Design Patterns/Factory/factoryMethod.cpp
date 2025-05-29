#include <iostream>

class DeliveryVehicle {
public:
    virtual void deliver() = 0;
    virtual ~DeliveryVehicle() = default;
};

class LandVehicle : public DeliveryVehicle {
public:
    void deliver() override {
        std::cout << "Delivering by land using a truck." << std::endl;
    }
};

class SeaVessel : public DeliveryVehicle {
public:
    void deliver() override {
        std::cout << "Delivering by sea using a ship." << std::endl;
    }
};

class DeliveryVehicleFactory {
public:
    virtual DeliveryVehicle* createVehicle() = 0; // Factory Method
    virtual ~DeliveryVehicleFactory() = default;
};

class LandDeliveryVehicleFactory : public DeliveryVehicleFactory {
public:
    DeliveryVehicle* createVehicle() override {
        return new LandVehicle();
    }
};

class SeaDeliveryVehicleFactory : public DeliveryVehicleFactory {
public:
    DeliveryVehicle* createVehicle() override {
        return new SeaVessel();
    }
};

int main() {
    DeliveryVehicleFactory* factory;

    bool deliverBySea = true;
    if (deliverBySea) {
        factory = new SeaDeliveryVehicleFactory();
    } else {
        factory = new LandDeliveryVehicleFactory();
    }

    DeliveryVehicle* vehicle = factory->createVehicle();
    vehicle->deliver();

    delete vehicle;
    delete factory;
}
