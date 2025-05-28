#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void best_auton() {
  // intentionally empty
}

void simple_auton() {
  // intentionally empty
}

void good_auton() {
  // intentionally empty
}


rd::Selector selector("Auton Selector", {
    {"Best auton", best_auton, LV_COLOR_RED},
    {"Simple auton", simple_auton, LV_COLOR_BLUE},
    {"Good auton", good_auton, LV_COLOR_GREEN}
});




void autonomous() {
	selector.run_auton();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */


 
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);

	pros::MotorGroup left_mg({-11, -12, -13});
  	pros::MotorGroup right_mg({18, 19, 20});

	while (true) {
		// Tank Control Scheme
		double left_speed = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		double right_speed = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

		left_mg.move(left_speed);
		right_mg.move(right_speed);
		pros::delay(20);

	}
	
	/*
	  pros::Controller master(pros::E_CONTROLLER_MASTER);

  // MotorGroups with reversed left side
  pros::MotorGroup left_mg({-11, -12, -13});
  pros::MotorGroup right_mg({18, 19, 20});

  // Exponential drive function (nested)
  auto exponentialDrive = [](double input) {
    double normalized = input / 127.0;
    double abs_x = std::abs(normalized);
    double y = 1.2 * std::pow(1.043, abs_x * 100.0) - 1.2 + 0.2 * abs_x;
    y *= (normalized >= 0) ? 1 : -1;
    return y * 127.0;
  };

  while (true) {
    double left_input = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    double right_input = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    double left_speed = exponentialDrive(left_input);
    double right_speed = exponentialDrive(right_input);

    left_mg.move(left_speed);
    right_mg.move(right_speed);

    pros::delay(20);
  }
	*/
}