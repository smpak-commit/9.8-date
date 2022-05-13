//#pragma once
//Chrono.h
#include <iostream>
//using namespace std;

namespace Chrono {

	enum class Month {
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};
	enum class Day {
		sunday, monday, tuesday, wednesday, thursday, friday, saturday
	};


	class Date {
	public:
		class Invalid {};
		Date(int y, Month m, int d);
		Date();

		//不改变对象的操作
		int day() const { return d; }
		Month month() const { return m; }
		int year() const { return y; }
		long int all_days() const { return iday; }

		//改变对象的操作
		void add_day(int n);
		void add_month(int n);
		void add_year(int n);
		void count_day();
	private:
		int y;
		Month m;
		int d;
		long int iday;
	};

	bool is_date(int y, Month m, int d);  //当日期合法时返回true
	bool leapyear(int y); //当是闰年时返回true

	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);
	bool operator>=(const Date& a, const Date& b);
	bool operator<=(const Date& a, const Date& b);

	std::ostream& operator<<(std::ostream& os, const Date& d);

	std::istream& operator>>(std::istream& is, Date& dd);

	Day day_of_week(const Date& dd);
	Date next_Sunday(const Date& dd);
	Date next_weekday(const Date& dd);
	Date next_workday(const Date& dd);
	int week_of_year(const Date& dd);

}				//Chrono