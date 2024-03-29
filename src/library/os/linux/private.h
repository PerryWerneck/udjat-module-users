/* SPDX-License-Identifier: LGPL-3.0-or-later */

/*
 * Copyright (C) 2021 Perry Werneck <perry.werneck@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

 #pragma once

 #include <config.h>
 #include <udjat/defs.h>
 #include <udjat/tools/user/session.h>
 #include <udjat/tools/user/list.h>

 #ifdef HAVE_DBUS
	#include <udjat/tools/dbus/connection.h>
 #endif // HAVE_DBUS

 namespace Udjat {

 #ifdef HAVE_DBUS
	class User::Session::Bus : public Udjat::DBus::NamedBus {
	public:
		Bus(const char *busname, const char *name) : Udjat::DBus::NamedBus{busname,name} {
		}

	};

	class User::List::Bus : public Udjat::DBus::SystemBus {
	public:
		Bus() : Udjat::DBus::SystemBus{} {
		}

	};

 #endif // HAVE_DBUS

 }


