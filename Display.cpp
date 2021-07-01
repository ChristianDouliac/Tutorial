#include "../include/Display.hpp"

using namespace cv;
using namespace cv_bridge;
using std::placeholders::_1;


namespace composition
{

	Display::Display(const rclcpp::NodeOptions & options) : Node("display", options)
	{
		this->instanciateROS2Parameters();
		
		this->subscription = this->create_subscription<sensor_msgs::msg::Image>(this->subTopicName, rclcpp::SensorDataQoS(), std::bind(&Display::listenerCallback, this, _1));
	}

	void Display::instanciateROS2Parameters()
	{
		this->subTopicNameDescriptor = ParameterDescriptor();
		this->subTopicNameDescriptor.description = "Name of the topic to subscribe to";
		this->subTopicNameDescriptor.type = rcl_interfaces::msg::ParameterType::PARAMETER_STRING;
		this->subTopicNameDescriptor.name = "sub_topic_name";
		this->declare_parameter("sub_topic_name", "SUB_TOPIC_NAME", this->subTopicNameDescriptor);
		this->subTopicName = this->get_parameter("sub_topic_name").as_string();

		this->windowNameDescriptor = ParameterDescriptor();
		this->windowNameDescriptor.description = "Name of the display window";
		this->windowNameDescriptor.type = rcl_interfaces::msg::ParameterType::PARAMETER_STRING;
		this->windowNameDescriptor.name = "window_name";
		this->declare_parameter("window_name", "WINDOW_NAME", this->windowNameDescriptor);
		this->windowName = this->get_parameter("window_name").as_string();

	}

	void Display::listenerCallback(const sensor_msgs::msg::Image::SharedPtr msg)
	{
		CvImagePtr cv_ptr = nullptr;

		try
		{
			cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
		}
		catch (cv_bridge::Exception& e)
		{
			RCLCPP_ERROR(this->get_logger(),"cv_bridge exception: %s", e.what());
			return;
		}

		
		imshow(this->windowName, cv_ptr->image);
		waitKey(1);


	}

	Display::~Display()
	{
		// To completed
		
	}
}

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(composition::Display)