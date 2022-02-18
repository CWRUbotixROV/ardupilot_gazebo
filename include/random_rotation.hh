#pragma once

#include <gazebo/common/common.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>

namespace gazebo
{
    class RandomRotation : public ModelPlugin
    {
        public:
        void Load(physics::ModelPtr parent, sdf::ElementPtr);

        void OnUpdate();

        private:
        physics::ModelPtr model;
        event::ConnectionPtr updateConnection;
        double roll;
        double pitch;
        double yaw;
    };

    GZ_REGISTER_MODEL_PLUGIN(RandomRotation)
}