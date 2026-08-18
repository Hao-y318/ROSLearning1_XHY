from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='topic_practice',
            executable='publisher',
            name='publisher_node',
        ),

        Node(
            package='topic_practice',
            executable='subscriber',
            name='subscriber_node',
        ),
    ])