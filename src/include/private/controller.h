/* SPDX-License-Identifier: LGPL-3.0-or-later */

/*
 * Copyright (C) 2024 Perry Werneck <perry.werneck@gmail.com>
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

 /**
  * @brief Declares user list controler/handler.
  */

 #pragma once
 #include <config.h>
 #include <udjat/defs.h>

 namespace Udjat {

	namespace User {

		/// @brief User session controller/watcher.
		class UDJAT_API Controller {
		private:

			std::mutex guard;

			/// @brief Session list.
			std::list<std::shared_ptr<Session>> sessions;

			/// @brief Agent list.
			std::list<Agent *> agents;

			/// @brief Initialize controller.
			void init() noexcept;

			/// @brief Deinitialize controller.
			void deinit() noexcept;

			/// @brief Initialize session.
			void init(std::shared_ptr<Session> session);

			/// @brief Deinitialize session.
			void deinit(std::shared_ptr<Session> session);

#ifdef _WIN32

			HWND hwnd = 0;
			static LRESULT WINAPI hwndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
			void load(bool starting) noexcept;

			// @brief			Find session by SID.
			// @param sid 		SID of the requested session.
			// @param create	If true will create a new session when not found.
			std::shared_ptr<Session> find(DWORD sid, bool create = true);

#else

			std::shared_ptr<Session> find(const char * sid);
			std::thread *monitor = nullptr;

			bool enabled = false;

			/// @brief Event fd
			int efd = -1;

			void wakeup();

			class Bus;
			std::shared_ptr<Bus> systembus;		///< @brief Connection with the system bus

#endif // _WIN32

			/// @brief System is going to sleep.
			void sleep();

			/// @brief System is resuming from sleep.
			void resume();

			/// @brief System is shutting down.
			void shutdown();

		protected:

			/// @brief Session factory called every time the controller detects a new user session.
			virtual std::shared_ptr<Session> SessionFactory() noexcept;

			/// @brief Update session list from system.
			void refresh() noexcept;

		public:
			Controller(Controller &) = delete;
			Controller(Controller *) = delete;

			Controller();
			virtual ~Controller();

			/// @brief Start monitor, load sessions.
			void activate();

			/// @brief Stop monitor, unload sessions.
			void deactivate();

			void for_each(std::function<void(std::shared_ptr<Session>)> callback);

			inline size_t size() const {
				return sessions.size();
			}

			inline auto begin() {
				return sessions.begin();
			}

			inline auto end() {
				return sessions.end();
			}

		};

	}

 }
