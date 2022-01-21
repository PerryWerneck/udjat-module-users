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

 #include "private.h"

 using namespace std;
 using namespace Udjat;

 UserList::Agent::Factory::Factory() : Udjat::Factory("user-list", &UserList::info) {
 }

 bool UserList::Agent::Factory::parse(Udjat::Abstract::Agent &parent, const pugi::xml_node &node) const {
	parent.insert(make_shared<UserList::Agent>(node));
	return true;
 }

 UserList::Agent::Agent(const pugi::xml_node &node) : Abstract::Agent(node), controller(UserList::Controller::getInstance()) {
	load(node);
	controller->insert(this);
 }

 UserList::Agent::~Agent() {
	controller->remove(this);
 }

 void UserList::Agent::append_alert(const pugi::xml_node &node) {
	alerts.push_back(make_shared<UserList::Alert>(node));
 }

 void UserList::Agent::onEvent(Udjat::User::Session &session, const Udjat::User::Event event) noexcept {

 	try {

		cout << session.to_string() << "\t" << EventDescription(event) << endl;

		for(auto alert : alerts) {
			alert->onEvent(alert,session,event);
		}

 	} catch(const std::exception &e) {
		cerr << getName() << "\t" << e.what() << endl;
 	}

 }