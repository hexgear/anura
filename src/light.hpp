/*
	Copyright (C) 2003-2013 by David White <davewx7@gmail.com>
	
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef LIGHT_HPP_INCLUDED
#define LIGHT_HPP_INCLUDED

#include "formula_callable.hpp"
#include "geometry.hpp"
#include "variant.hpp"

#include <boost/intrusive_ptr.hpp>

class custom_object;
class light;

typedef boost::intrusive_ptr<light> light_ptr;
typedef boost::intrusive_ptr<const light> const_light_ptr;

class light : public game_logic::formula_callable
{
public:
	static light_ptr create_light(const custom_object& obj, variant node);

	virtual variant write() const = 0;

	explicit light(const custom_object& obj);
	virtual ~light();
	virtual void process() = 0;
	virtual bool on_screen(const rect& screen_area) const = 0;
	virtual void draw(const rect& screen_area, const unsigned char* color) const = 0;
protected:
	const custom_object& object() const { return obj_; }
private:
	virtual variant get_value(const std::string& key) const;
	const custom_object& obj_;
};

class circle_light : public light
{
public:
	circle_light(const custom_object& obj, variant node);
	circle_light(const custom_object& obj, int radius);
	variant write() const;
	void process();
	bool on_screen(const rect& screen_area) const;
	void draw(const rect& screen_area, const unsigned char* color) const;
private:
	point center_;
	int radius_;
};

class light_fade_length_setter
{
	int old_value_;
public:
	explicit light_fade_length_setter(int value);
	~light_fade_length_setter();
};

#endif
