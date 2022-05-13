//Chrono.cpp

#include "Chrono.h"

namespace Chrono {
	//成员函数定义

	Date::Date(int yy, Month mm, int dd)
		:y{ yy }, m{ mm }, d{ dd },iday{0}
	{
		if (!is_date(yy, mm, dd)) throw Invalid{};
	}

	const Date& default_date()
	{
		static Date dd{ 1970,Month::jan,1 };
		return dd;
	}

	Date::Date()
		:y{ default_date().year() },
		m{ default_date().month() },
		d{ default_date().day() },
		iday{ 0 }
	{
	}

	void Date::add_day(int n)
	{
		int leftn = n;
		while (true)
		{
			int days_in_month = 31;
			switch (m)
			{
			case Chrono::Month::feb:
				days_in_month = (leapyear(y)) ? 29 : 28;
				break;

			case Chrono::Month::apr:
			case Chrono::Month::jun:
			case Chrono::Month::sep:
			case Chrono::Month::nov:
				days_in_month = 30;
				break;
			}
			if ((leftn + d) <= days_in_month)
			{
				d += leftn;
				break;
			}

			m = (m == Month::dec) ? Month::jan : Month(int(m) + 1);
			if (m == Month::jan)
				++y;

			leftn = leftn + d - days_in_month;
			if (leftn > days_in_month)
			{
				d = 1;
				--leftn;
			}
			else
			{
				d = leftn;
				break;
			}
		}
	}

	void Date::add_month(int n)
	{
		for (int i = 0;i < n;++i)
		{
			m = (m == Month::dec) ? Month::jan : Month(int(m) + 1);
			if (m == Month::jan)
				add_year(1);

			int days_in_month = 31;
			switch (m)
			{
			case Month::feb:
				days_in_month = leapyear(y) ? 29 : 28;
				break;
			case Month::apr:case Month::jun:case Month::sep:case Month::nov:
				days_in_month = 30;
				break;
			}
			d = (d >= days_in_month) ? days_in_month : d;
		}
	}

	void Date::add_year(int n)
	{
		if (m == Month::feb && d == 29 && !leapyear(y + n)) {  //如果是闰年，且是2月29日，则要用3月1日代替
			m = Month::mar;
			d = 1;
		}
		y += n;
	}

	void Date::count_day()
	{
		iday = 0;
		Date beg_date{ default_date() };
		Date end_date{ Date{2099,Month::dec,31} };
		Date find_date{ Date{y,m,d} };
		if (!(find_date >= beg_date && find_date <= end_date)) return;

		//year
		while (beg_date.y < find_date.y)
		{
			iday += (leapyear(beg_date.y) ? 366 : 365);
			beg_date.add_year(1);
		}

		//month
		for (int i=1; i < int(find_date.m);++i)
		{
			int days_in_month = 31;
			switch (Month(i))
			{
			case Chrono::Month::feb:
				days_in_month = (leapyear(find_date.y)) ? 29 : 28;
				break;

			case Chrono::Month::apr:
			case Chrono::Month::jun:
			case Chrono::Month::sep:
			case Chrono::Month::nov:
				days_in_month = 30;
				break;
			}
		
			iday += days_in_month;
		}
		
		//day
		iday += find_date.d-1;
	}

/*
	void Date::count_day()
	{
		iday = 0;
		Date beg_date{ default_date() };
		Date end_date{ Date{2099,Month::dec,31} };
		Date find_date{ Date{y,m,d} };
		if (!(find_date >= beg_date && find_date <= end_date)) return;

		long int i=0, j=47481, half=47481/2;
		while (i<j)
		{
			Date tmp_date{ beg_date };
			tmp_date.add_day(half);
			if (find_date <= tmp_date)
				if (find_date == tmp_date)
				{
					iday = half;
					return;
				}
				else
				{
					j = half;
					half = (j-i) / 2 + i;
				}
			else
			{
				i = half;
				half = (j - i) / 2 + i;
			}
		}
	}
*/
	//辅助函数

	bool is_date(int y, Month m, int d)
	{
		if (y < 1900 || 2099 < y) return false;
		if (m < Month::jan || Month::dec < m) return false;
		if (d < 1) return false;

		int days_in_month = 31; //大多数月份为31天

		switch (m) {
		case Month::feb:
			days_in_month = (leapyear(y)) ? 29 : 28;
			break;

		case Month::apr:case Month::jun:case Month::sep:case Month::nov:
			days_in_month = 30;
			break;
		}

		if (d > days_in_month) return false;

		return true;
	}

	bool leapyear(int y)
	{
		return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
	}

	bool operator==(const Date& a, const Date& b)
	{
		return a.year() == b.year()
			&& a.month() == b.month()
			&& a.day() == b.day();
	}

	bool operator!=(const Date& a, const Date& b)
	{
		return !(a == b);
	}

	bool operator>=(const Date& a, const Date& b)
	{
		return a.year() > b.year() 
			|| a.year() == b.year() && a.month() > b.month()
			|| a.year() == b.year() && b.month() == b.month() && a.day() >= b.day();
	}

	bool operator<=(const Date& a, const Date& b)
	{
		return a.year() < b.year()
			|| a.year() == b.year() && a.month() < b.month()
			|| a.year() == b.year() && a.month() == b.month() && a.day() <= b.day();
	}

	std::ostream& operator<<(std::ostream& os, const Date& d)
	{
		return os << '(' << d.year() << '-' << int(d.month()) << '-' << d.day() << ')';
	}

	std::istream& operator>>(std::istream& is, Date& dd)
	{
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if (!is) return is;
		if (ch1 != '(' || ch2 != '-' || ch3 != '-' || ch4 != ')') { //格式错误
			is.clear(std::ios_base::failbit);							//设置failbit
			return is;
		}

		dd = Date(y, Month(m), d);  //更新dd

		return is;
	}

	//w=y + (y/4) + (c/4) - 2*c + (26*(m+1)/10) + d -1; //蔡勒公式得到星期
	Day day_of_week(const Date& dd)
	{
		int iweek = 0;
		unsigned int y = 0, c = 0, m = 0, d = 0;

		switch(dd.month())
		{
		case Month::jan:case Month::feb:
		{
			c = (dd.year() - 1) / 100;
			y = (dd.year() - 1) % 100;
			m = int(dd.month()) + 12;
			d = dd.day();
			break;
		}
		default:
		{
			c = dd.year() / 100;
			y = dd.year() % 100;
			m = int(dd.month());
			d = dd.day();
			break;
		}
		}
		iweek = y + (y / 4) + (c / 4) - 2*c + (26 * (m + 1) / 10) + d - 1;
		iweek = (iweek >= 0) ? (iweek % 7) : (iweek % 7 + 7); 
		return Day(iweek);
	}

	Date next_Sunday(const Date& dd)
	{
		Day iweekday = day_of_week(dd);
		int i = 7 - int(iweekday);
		Date next_day{ dd };
		next_day.add_day(i);
		return next_day;
	}

	Date next_weekday(const Date& dd)
	{
		Day iweekday = day_of_week(dd);
		int i = (iweekday == Day::sunday) ? 1 : (8 - int(iweekday));
		Date next_day{ dd };
		next_day.add_day(i);
		return next_day;
	}

	Date next_workday(const Date& dd)
	{
		Day iweekday = day_of_week(dd);
		int i{int(iweekday)};
		switch (iweekday)
		{
		case Day::friday:
			i = 3;
			break;
		case Day::saturday:
			i = 2;
			break;
		
		default:
			i=1;
			break;
		}
		Date next_day{ dd };
		next_day.add_day(i);
		return next_day;
	}

	int week_of_year(const Date& dd)
	{
		Date beg_day{ Date{ dd.year(),Month(1),1 } };
		Date end_day = next_Sunday(beg_day);
		int iweek = 1;
		while (true) {
			if (dd>=beg_day&&dd<=end_day)
				break;
			end_day.add_day(1);
			beg_day = end_day;
			end_day = next_Sunday(end_day);
			++iweek;			
		}
		return iweek;
	}
}