# Obstacle-Car-Project
This project builds an autonomous car controlled by an Arduino Uno that utilizes three ultrasonic sensors to detect obstacles and navigate around them.
# Components:
• Arduino Uno <br/>
• L298N Motor Driver Module  <br/>
• DC Gear Motors (2x)  <br/>
• Caster Wheel (1x)  <br/>
• Ultrasonic Sensors (3x)  <br/>
• Breadboard and Jumper Wires  <br/>
• Power Source (Battery Pack or DC Adapter)  <br/>

# Assembly Instructions:

1.Chassis Construction: Create a chassis using materials like acrylic, wood, or Lego. Ensure it can accommodate the motors, sensors, and Arduino board. <br/>
2.Motor and Wheel Connection: Mount the DC gear motors on the chassis, attaching wheels to their shafts. The caster wheel should be placed at the front for better maneuverability. <br/>
3.L298N Motor Driver: Connect the L298N module to the Arduino according to its datasheet. This module will control the motor direction and speed. <br/>
4.Ultrasonic Sensor Placement: Position the three ultrasonic sensors strategically on the front of the car. One can be centered, and the other two can be placed slightly outwards for broader obstacle detection. Refer to the sensor's datasheet for proper wiring connections to the Arduino.<br/>

# Code Explanation:
The Arduino code will continuously read the distance readings from the three ultrasonic sensors. Based on these readings, it will determine if an obstacle is present and in which direction. The car will then take appropriate actions to avoid the obstacle, such as turning left, right, or reversing.<br/>

# Calibration:

1.Experiment with different trigger and echo pin connections based on your sensor and motor driver setup.<br/>
2.Adjust the maximum distance values in the NewPing objects according to your sensor's specifications.<br/>
3.Define a threshold distance in the obstacleDetected function to determine when an obstacle is close enough to trigger avoidance maneuvers.<br/>
4.Test the car's behavior in different environments and fine-tune the code to optimize obstacle detection and avoidance strategies.<br/>


# Safety:
• Use caution when operating the car, especially around people and pets.<br/>
• Start with low motor speeds during testing to minimize the risk of damage if the car collides with obstacles.<br/>

# Additional Notes:

1.Consider implementing a safety feature that stops the car completely if all three sensors detect obstacles within a very close range.<br/>
2.Explore advanced obstacle avoidance algorithms such as fuzzy logic or PID control for more refined navigation.<br/>




