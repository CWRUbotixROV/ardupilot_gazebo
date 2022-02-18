#include "include/random_rotation.hh"

using namespace gazebo;

void RandomRotation::Load(physics::ModelPtr parent, sdf::ElementPtr sdf)
{
    model = parent;
    roll = sdf->Get<double>("roll");
    pitch = sdf->Get<double>("pitch");
    yaw = sdf->Get<double>("yaw");

    this->updateConnection = event::Events::ConnectWorldUpdateBegin(std::bind(&RandomRotation::OnUpdate, this));
}

void RandomRotation::OnUpdate()
{
    double newRoll = ignition::math::Rand::DblUniform(-roll, roll);
    double newPitch = ignition::math::Rand::DblUniform(-pitch, pitch);
    double newYaw = ignition::math::Rand::DblUniform(-yaw, yaw);

    ignition::math::v6::Pose3 pose = model->RelativePose();
    pose.Set(pose.Pos(), ignition::math::v6::Vector3d(newRoll, newPitch, newYaw));
    model->SetRelativePose(pose);
}