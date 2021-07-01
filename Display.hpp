#ifndef DISPLAY_H
#define DISPLAY_H


#include "rclcpp/rclcpp.hpp"
#include "rclcpp/node.hpp"
#include "rclcpp/qos.hpp"
#include "rclcpp/parameter.hpp"
#include "../../include/visibility_control.h"

#include "rcl_interfaces/msg/parameter_type.hpp"
#include "rcl_interfaces/msg/parameter_descriptor.hpp"

#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"

#include "opencv2/core/core.hpp"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace rclcpp;
using namespace rcl_interfaces::msg;
using namespace std;
using namespace sensor_msgs::msg;
using namespace cv_bridge;


// Blabla test 

namespace composition
{
    class Display : public rclcpp::Node
    {
        private:
            void instanciateROS2Parameters();

            void listenerCallback(const Image::SharedPtr msg);

            ParameterDescriptor subTopicNameDescriptor;
            string subTopicName;

            ParameterDescriptor windowNameDescriptor;
            string windowName;

            Subscription<Image>::SharedPtr subscription;        

        public:
            explicit Display(const rclcpp::NodeOptions & options);
            ~Display();
    };
}

#endif