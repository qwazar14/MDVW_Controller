#include "fiber_pool.hpp"
#include "util/vehicle.hpp"
#include "views/view.hpp"
#include "util/mobile.hpp"
#include "core/data/speed_units.hpp"

namespace big
{
	void view::vehicle()
	{
		components::button("MMI Fix All PV", [] {
			int amount_fixed = mobile::mors_mutual::fix_all();
			g_notification_service->push("Mobile",
				std::format("{} vehicle{} been fixed.", amount_fixed, amount_fixed == 1 ? " has" : "s have")
			);
		});
		ImGui::SameLine();
		components::button("Repair", [] {
			vehicle::repair(self::veh);
		});

		ImGui::SameLine();
		components::command_checkbox<"keepfixed">();

		ImGui::Separator();

		components::button("Teleport in PV", [] {
			Vehicle veh = mobile::mechanic::get_personal_vehicle();
			teleport::into_vehicle(veh);
		});
		ImGui::SameLine();
		components::button("Bring PV", [] {
			Vehicle veh = mobile::mechanic::get_personal_vehicle();
			vehicle::bring(veh, self::pos, true);
		});
		ImGui::SameLine();
		components::button("Bring Closest Vehicle", [] {
			Vehicle veh = vehicle::get_closest_to_location(self::pos, 200);
			vehicle::bring(veh, self::pos, true, -1);
		});

		ImGui::Separator();

		components::button("Turn Engine On", [] {
			vehicle::set_engine_state(
				self::veh,
				true,
				g.vehicle.change_engine_state_immediately,
				g.vehicle.disable_engine_auto_start
			);
		});
		ImGui::SameLine();
		components::button("Turn Engine Off", [] {
			vehicle::set_engine_state(
				self::veh,
				false,
				g.vehicle.change_engine_state_immediately,
				g.vehicle.disable_engine_auto_start
			);
		});
		ImGui::Checkbox("Disable Engine Auto Start", &g.vehicle.disable_engine_auto_start);
		ImGui::SameLine();
		ImGui::Checkbox("Change State Immediately", &g.vehicle.change_engine_state_immediately);

		ImGui::Separator();

		components::sub_title("General");
		{
			ImGui::BeginGroup();

			ImGui::Checkbox("God Mode", &g.vehicle.god_mode);
			components::command_checkbox<"hornboost">();
			components::command_checkbox<"vehjump">();
			components::command_checkbox<"invisveh">();
			if (g.vehicle.vehinvisibility)
			{
				components::command_checkbox<"localinvisveh">();
				components::command_checkbox<"localinvisped">();
			}

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();

			components::command_checkbox<"instantbrake">();
			components::command_checkbox<"blockhoming">();
			components::command_checkbox<"driveonwater">();

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();

			components::command_checkbox<"seatbelt">();
			ImGui::Checkbox("Turn Signals", &g.vehicle.turn_signals);
			if (g.vehicle.turn_signals)
			{
				ImGui::Checkbox("Fully Automatic Signal", &g.vehicle.auto_turn_signals);
			}
			components::command_checkbox<"driveunder">();

			ImGui::EndGroup();
		}
		ImGui::Separator();


		components::sub_title("Proofs");
		{
			if (ImGui::Button("Check all"))
			{
				g.vehicle.proof_bullet = true;
				g.vehicle.proof_fire = true;
				g.vehicle.proof_collision = true;
				g.vehicle.proof_melee = true;
				g.vehicle.proof_explosion = true;
				g.vehicle.proof_steam = true;
				g.vehicle.proof_water = true;
			}

			ImGui::SameLine();

			if (ImGui::Button("Uncheck all"))
			{
				g.vehicle.proof_bullet = false;
				g.vehicle.proof_fire = false;
				g.vehicle.proof_collision = false;
				g.vehicle.proof_melee = false;
				g.vehicle.proof_explosion = false;
				g.vehicle.proof_steam = false;
				g.vehicle.proof_water = false;
			}

			ImGui::BeginGroup();

			ImGui::Checkbox("Bullet", &g.vehicle.proof_bullet);
			ImGui::Checkbox("Fire", &g.vehicle.proof_fire);

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();

			ImGui::Checkbox("Collision", &g.vehicle.proof_collision);
			ImGui::Checkbox("Melee", &g.vehicle.proof_melee);

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();

			ImGui::Checkbox("Explosion", &g.vehicle.proof_explosion);
			ImGui::Checkbox("Steam", &g.vehicle.proof_steam);

			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::BeginGroup();

			ImGui::Checkbox("Water", &g.vehicle.proof_water);

			ImGui::EndGroup();
		}
		ImGui::Separator();


		components::sub_title("Speed Unit");
		{
			ImGui::RadioButton(
				speed_unit_strings[(int)SpeedUnit::KMPH].c_str(),
				(int*)&g.vehicle.speed_unit,
				(int)SpeedUnit::KMPH
			);
			ImGui::SameLine();
			ImGui::RadioButton(
				speed_unit_strings[(int)SpeedUnit::MIPH].c_str(),
				(int*)&g.vehicle.speed_unit,
				(int)SpeedUnit::MIPH
			);
			ImGui::SameLine();
			ImGui::RadioButton(
				speed_unit_strings[(int)SpeedUnit::MPS].c_str(),
				(int*)&g.vehicle.speed_unit,
				(int)SpeedUnit::MPS
			);
		}
		ImGui::Separator();

		components::sub_title("Speedo Meter");
		{
			ImGui::Checkbox("Enabled", &g.vehicle.speedo_meter.enabled);

			if (g.vehicle.speedo_meter.enabled)
			{
				ImGui::Text("Position (X, Y)");

				float pos[2] = { g.vehicle.speedo_meter.x, g.vehicle.speedo_meter.y };

				if (ImGui::SliderFloat2("###speedo_pos", pos, .001f, .999f, "%.3f"))
				{
					g.vehicle.speedo_meter.x = pos[0];
					g.vehicle.speedo_meter.y = pos[1];
				}

				ImGui::SameLine();

				ImGui::Checkbox("Left Sided", &g.vehicle.speedo_meter.left_side);
			}
		}

		g.vehicle.proof_mask = 0;
		if (g.vehicle.god_mode)
		{
			g.vehicle.proof_mask |= static_cast<int>(eEntityProofs::GOD);
		}
		if (g.vehicle.proof_bullet)
		{
			g.vehicle.proof_mask |= static_cast<int>(eEntityProofs::BULLET);
		}
		if (g.vehicle.proof_fire)
		{
			g.vehicle.proof_mask |= static_cast<int>(eEntityProofs::FIRE);
		}
		if (g.vehicle.proof_collision)
		{
			g.vehicle.proof_mask |= static_cast<int>(eEntityProofs::COLLISION);
		}
		if (g.vehicle.proof_melee)
		{
			g.vehicle.proof_mask |= static_cast<int>(eEntityProofs::MELEE);
		}
		if (g.vehicle.proof_explosion)
		{
			g.vehicle.proof_mask |= static_cast<int>(eEntityProofs::EXPLOSION);
		}
		if (g.vehicle.proof_steam)
		{
			g.vehicle.proof_mask |= static_cast<int>(eEntityProofs::STEAM);
		}
		if (g.vehicle.proof_water)
		{
			g.vehicle.proof_mask |= static_cast<int>(eEntityProofs::WATER);
		}
	}
}
