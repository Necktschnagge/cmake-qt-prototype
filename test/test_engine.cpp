#include "gtest/gtest.h"

#include "../src/engine.h"

#include <type_traits>
#include <array>

TEST(engine, create_division_by_2_error) {
	ASSERT_NO_THROW(
		tobor::v1_0::division_by_2_error error;
	);
}

TEST(engine, create_blocked_center_error) {
	ASSERT_NO_THROW(
		tobor::v1_0::blocked_center_error error;
	);
}

TEST(engine, create_wall_type_std_constructor) {
	ASSERT_FALSE(
		std::is_default_constructible<tobor::v1_0::wall_type>::value // convert into static assert! ###
	);
}

TEST(engine, create_wall_type_bool_conversion) {
	ASSERT_NO_THROW(
		auto t_wall = tobor::v1_0::wall_type(true);
	auto f_wall = tobor::v1_0::wall_type(false);
	);
}

TEST(engine, create_world) {
	ASSERT_NO_THROW(
		tobor::v1_0::tobor_world world;
	);
}

TEST(engine, create_universal_field_id) {
	ASSERT_NO_THROW(
		auto field_id = tobor::v1_0::universal_field_id();
	);
}

TEST(engine, universal_field_id_consistency) {
	// ### check that id conversion has no inconsistencies...
	ASSERT_NO_THROW(
		auto field_id = 0;
	);
}



TEST(engine, example_integration) {
	// check the following scenario:
	// create world
	// create initial robots position
	// run solver

	auto w = tobor::v1_0::tobor_world(16, 16);

	w.block_center_fields(2, 2);

	// add vertical walls row by row, starting left
	w.west_wall_by_id(w.field_id_of(6, 0)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(12, 0)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(2, 1)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(10, 1)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(7, 3)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(14, 3)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(1, 4)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(11, 4)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(13, 5)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(4, 6)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(12, 9)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(7, 10)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(14, 10)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(3, 11)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(7, 13)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(10, 13)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(1, 14)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(13, 14)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(4, 15)).is_wall = true;
	w.west_wall_by_id(w.field_id_of(12, 15)).is_wall = true;

	w.south_wall_by_transposed_id(w.transposed_field_id_of(0, 2)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(0, 10)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(1, 4)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(1, 14)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(2, 2)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(2, 11)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(3, 7)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(6, 3)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(6, 14)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(7, 11)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(9, 2)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(9, 13)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(10, 4)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(11, 10)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(13, 6)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(13, 15)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(14, 3)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(14, 10)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(15, 7)).is_wall = true;
	w.south_wall_by_transposed_id(w.transposed_field_id_of(15, 12)).is_wall = true;

	// specify initial state
	auto target_robot = tobor::v1_0::universal_field_id::create_by_coord(6, 9, w);
	auto green_robot = tobor::v1_0::universal_field_id::create_by_coord(12, 7, w);
	auto red_robot = tobor::v1_0::universal_field_id::create_by_coord(12, 12, w);
	auto yellow_robot = tobor::v1_0::universal_field_id::create_by_coord(6, 14, w);

	std::array<tobor::v1_0::universal_field_id, 3> other_robots{ green_robot, red_robot, yellow_robot };

	//auto initial_state = tobor::v1_0::robots_position_state<3>(target_robot, std::move(other_robots));

	// specify target field
	auto target = tobor::v1_0::universal_field_id::create_by_coord(9, 1, w);

	auto w_analyzer = tobor::v1_0::tobor_world_analyzer<3>(w);

	auto optimal_solution_length = tobor::v1_0::get_all_optimal_solutions<3>(w_analyzer , target, target_robot, std::move(other_robots));

	ASSERT_EQ(9, optimal_solution_length);

}

