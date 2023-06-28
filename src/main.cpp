#include "logger.h"
#include "engine.h"

#include <string>
#include <numeric>

#include <fstream>

// tobor colors: 
// red		#f4191c
// yellow	#ffbd02
// green	#00a340
// blue		#4285f4

class svg_generator {

	static std::string get_xml_header() {
		return R"xxx(<?xml version="1.0" standalone="no"?>
)xxx";
	}

	static std::string wrap_svg(const std::string& height, const std::string& width, const std::string& nested_content) {
		(void)height;
		(void)width;
		(void)nested_content;
		return std::string();
	}
	//< svg width = "6400" height = "1600" version = "1.1" xmlns = "http://www.w3.org/2000/svg" >



public:
	static std::string create_svg() {
		std::string svg_result;

		return svg_result;
	}


	virtual std::string get_svg() const = 0;

	virtual ~svg_generator() {
	}

};

class xml_header : public svg_generator {

public:
	virtual std::string get_svg() const override {
		return R"xxx(<?xml version="1.0" standalone="no"?>
)xxx";
	}
};


class svg_environment : public svg_generator {

	static std::string wrap_svg(const std::string& height, const std::string& width, const std::string& nested_content) {
		return std::string(R"---(<svg height=")---")
			+ height
			+ R"---(" width=")---"
			+ width
			+ R"---(" version="1.1" xmlns="http://www.w3.org/2000/svg">
)---"
+ nested_content
+ "</svg>";
	}

	std::unique_ptr<svg_generator> body;
	std::string height;
	std::string width;

public:

	svg_environment(const std::string& height, const std::string& width, std::unique_ptr<svg_generator> body) :
		body(std::move(body)),
		height(height),
		width(width)
	{}

	virtual std::string get_svg() const override {
		return wrap_svg(height, width, body->get_svg());
	}

};

class svg_compound : public svg_generator {

public:

	using u_ptr = std::unique_ptr<svg_generator>;

	std::vector<u_ptr> elements;

	svg_compound() {}

	//svg_compound(std::initializer_list<std::unique_ptr<svg_compound>> init) : elements(init) {}

	template<class... T>
	svg_compound(T&&... init) {
		((void)elements.push_back(std::forward<T>(init)), ...);
	}

	virtual std::string get_svg() const override {
		return std::accumulate(
			elements.cbegin(),
			elements.cend(),
			std::string(),
			[](const std::string& acc, const u_ptr& el) {
				return acc + el->get_svg();
			});
	}
};

class svg_primitive : public svg_generator {

public:

	using u_ptr = std::unique_ptr<svg_generator>;

	//std::vector<u_ptr> elements;
	std::string primitive;

	svg_primitive() {}

	//svg_compound(std::initializer_list<std::unique_ptr<svg_compound>> init) : elements(init) {}

	//template<class... T>
	svg_primitive(const std::string& primitive) : primitive(primitive) {}

	virtual std::string get_svg() const override {
		return primitive;
	}
};


class svg_path : public svg_generator {

public:

	class element {

	public:

		virtual std::string str() const = 0;

		virtual std::shared_ptr<element> clone() const = 0;

	};

	template <class Number>
	class M : public element {

		friend class svg_path;

	public:

		std::vector<std::pair<Number, Number>> coordinates;

		M(const Number& x, const Number& y) : coordinates({ std::make_pair(x,y) })
		{
		}

		M() : M(0, 0) {}

		virtual std::string str() const override {
			return std::accumulate(coordinates.cbegin(), coordinates.cend(), std::string("M"),
				[](const std::string& acc, const std::pair<Number, Number>& el) -> std::string {
					return acc + " " + std::to_string(el.first) + " " + std::to_string(el.second);
				}
			);
		}

		virtual std::shared_ptr<element> clone() const {
			return std::make_shared< M>(*this);
		}
	};

	class Z : public element {

	public:

		Z() {}

		virtual std::string str() const override {
			return "Z";
		}

		virtual std::shared_ptr<element> clone() const {
			return std::make_shared< Z>(*this);
		}
	};

	template <class Number>
	class l : public element {

		friend class svg_path;

		std::vector<std::pair<Number, Number>> coordinates;

	public:

		l(const Number& x, const Number& y) : coordinates({ std::make_pair(x,y) })
		{
		}

		inline void add_coordinates() const noexcept {}

		template<class... _Rest>
		void add_coordinates(const Number& x, const Number& y, _Rest&& ... others) {
			coordinates.emplace_back(x, y);
			add_coordinates(std::forward<_Rest>(others) ...);
		}


		template<class... _Rest>
		l(const Number& x, const Number& y, _Rest&& ... others) : coordinates({ std::make_pair(x,y) })
		{
			add_coordinates(std::forward<_Rest>(others) ...);
		}

		virtual std::string str() const override {
			return std::accumulate(coordinates.cbegin(), coordinates.cend(), std::string("l"),
				[](const std::string& acc, const std::pair<Number, Number>& el) -> std::string {
					return acc + " " + std::to_string(el.first) + " " + std::to_string(el.second);
				}
			);
		}

		virtual std::shared_ptr<element> clone() const {
			return std::make_shared<l>(*this);
		}
	};

	//using u_ptr = std::unique_ptr<svg_generator>;

	using map = std::map<std::string, std::string>;

	map other_properties;


	std::vector<std::shared_ptr<element>> path_elements;

	svg_path() {}

	svg_path(const svg_path& other) : other_properties(other.other_properties){
		std::transform(
			other.path_elements.cbegin(),
			other.path_elements.cend(),
			std::back_inserter(this->path_elements),
			[](const std::shared_ptr<element>& el) {
				return el->clone();
			}
		);
	}

	svg_path(svg_path&& other) = delete;

	svg_path& operator = (const svg_path& other) = delete;

	svg_path& operator = (svg_path&& other) = delete;


	virtual std::string get_svg() const override {
		auto result = std::string("<path");

		result += std::string(" d=\"") +
			std::accumulate(
				path_elements.cbegin(),
				path_elements.cend(),
				std::string(""),
				[](const std::string& acc, const std::shared_ptr<element>& el) -> std::string {
					return acc + " " + el->str();
				})
			+ "\"";
				result += std::accumulate(
					other_properties.cbegin(),
					other_properties.cend(),
					std::string(""),
					[](std::string& acc, const map::value_type& el) -> std::string {
						return acc + " " + el.first + "=" + "\"" + el.second + "\"";
					});
				result += std::string("/>");
				return result;
	}

	auto fill() -> decltype(other_properties["fill"]) {
		return other_properties["fill"];
	}
	auto stroke() -> decltype(other_properties["stroke"]) {
		return other_properties["stroke"];
	}
	auto stroke_width() -> decltype(other_properties["stroke-width"]) {
		return other_properties["stroke-width"];
	}
	auto stroke_linecap() -> decltype(other_properties["stroke-linecap"]) {
		return other_properties["stroke-linecap"];
	}
	auto stroke_linejoin() -> decltype(other_properties["stroke-linejoin"]) {
		return other_properties["stroke-linejoin"];
	}
};

void test() {

	auto grid0 = std::make_unique<svg_path>();

	grid0->fill() = "dimgrey"; // !80 #0F54DA";
	grid0->stroke() = grid0->fill();
	grid0->stroke_width() = "0";
	//grid0->stroke_linecap() = "round";
	//grid0->stroke_linejoin() = grid0->stroke_linecap();

	constexpr double HALF_GRID_LINE_WIDTH{ 1.5 };

	int64_t count_rows{ 16 };
	int64_t count_cols{ 16 };

	auto grid0e0 = std::make_shared<svg_path::M<double>>(50.0 - HALF_GRID_LINE_WIDTH, 50.0 - HALF_GRID_LINE_WIDTH);

	auto grid0e1 = std::make_shared<svg_path::l<double>>(
		HALF_GRID_LINE_WIDTH * 2, 0,
		0, count_rows * 100 + HALF_GRID_LINE_WIDTH * 2,
		-HALF_GRID_LINE_WIDTH * 2, 0
	);
	auto grid0e2 = std::make_shared<svg_path::Z>();

	grid0->path_elements.push_back(grid0e0);
	grid0->path_elements.push_back(grid0e1);
	grid0->path_elements.push_back(grid0e2);

	auto grid1 = std::make_unique<svg_path>();
	grid1->fill() = "dimgrey"; // !80 #0F54DA";
	grid1->stroke() = grid0->fill();
	grid1->stroke_width() = "0";

	auto grid1e0 = std::make_shared<svg_path::M<double>>(50.0 - HALF_GRID_LINE_WIDTH, 50.0 - HALF_GRID_LINE_WIDTH);

	auto grid1e1 = std::make_shared<svg_path::l<double>>(
		count_cols * 100 + HALF_GRID_LINE_WIDTH * 2, 0,
		0, HALF_GRID_LINE_WIDTH * 2,
		-(count_cols * 100 + HALF_GRID_LINE_WIDTH * 2), 0
	);
	auto grid1e2 = std::make_shared<svg_path::Z>();

	grid1->path_elements.push_back(grid1e0);
	grid1->path_elements.push_back(grid1e1);
	grid1->path_elements.push_back(grid1e2);

	auto grid0_2 = std::make_unique<svg_path>(*grid0);

	dynamic_cast<svg_path::M<double>&> (*(grid0_2->path_elements[0])).coordinates[0].first += 100;




	const std::string test_s{ R"xxx(<path d="M 10 70 l 200 100 l 200 50 z"
        fill="red" stroke="blue" stroke-width="3" />
)xxx"};
	const std::string test_s2{ R"xxx(<path d="M 0 0 h 400 v 400 h -400 v -400 z"
        fill="grey" stroke="black" stroke-width="10" />
)xxx"};

	auto example_path_element = std::make_unique<svg_primitive>(test_s);
	auto outside_box = std::make_unique<svg_primitive>(test_s2);

	//<rect width="100%" height="100%" fill="grey" />

	auto background = std::make_unique<svg_path>();
	background->fill() = "lightyellow";
	background->stroke_width() = "0";
	background->stroke() = background->fill();

	auto b_e0 = std::make_shared<svg_path::M<double>>(0,0);
	auto b_e1 = std::make_shared<svg_path::l<double>>(1700, 0, 0, 1700, -1700, 0);
	auto b_e2 = std::make_shared<svg_path::Z>();

	background->path_elements.push_back(b_e0);
	background->path_elements.push_back(b_e1);
	background->path_elements.push_back(b_e2);


	auto grid = std::make_unique<svg_compound>(std::move(background), std::move(grid0), std::move(grid0_2), std::move(grid1));
	auto walls = std::make_unique<svg_compound>();// std::move(example_path_element), std::move(outside_box));
	auto robots = std::make_unique<svg_compound>();

	auto body = std::make_unique<svg_compound>(
		std::move(grid),
		std::move(walls),
		std::move(robots)
	);

	auto svg_env = std::make_unique<svg_environment>("1700", "1700", std::move(body));
	// each cell is 100 x 100
	// on each side we define a padding of 50. -> canvas is 1700 ^2


	svg_compound svg_file;
	svg_file.elements.emplace_back(std::make_unique<xml_header>());
	svg_file.elements.emplace_back(std::move(svg_env));

	standard_logger()->info(svg_file.get_svg());

	auto fs = std::ofstream(R"(C:\Users\F-NET-ADMIN\Desktop\preview.svg)");

	fs << svg_file.get_svg();
	/*
	*/

}
#if false
#endif


int main()
{
	init_logger();
	test();
	return 0;
}

