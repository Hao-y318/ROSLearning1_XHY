from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():

    package_path = get_package_share_directory('hello_yaml')

    yaml_file = os.path.join(
        package_path,
        'config',
        'hello_yaml.yaml'
    )

    return LaunchDescription([
        Node(
            package='hello_yaml',
            executable='hello_yaml',
            name='hello_yaml_node',
            output='screen',
            parameters=[yaml_file]
        )
    ])