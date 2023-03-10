#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_other()
	{
		if (ImGui::BeginTabItem("Other"))
		{
			ImGui::Text("Acceleration Multiplier");
			ImGui::DragFloat("###handling_acceleration", &g_local_player->m_vehicle->m_handling_data->m_acceleration, 1.f, 0.f, 50.f);

			ImGui::Text("Downforce Multiplier");
			ImGui::DragFloat("###handling_downforce", &g_local_player->m_vehicle->m_handling_data->m_downforce_multiplier, 1.f, 0.f, 50.f);

			ImGui::Text("Initial Drive Max Flat Vel");
			ImGui::DragFloat("###m_initial_drive_max_flat_vel", &g_local_player->m_vehicle->m_handling_data->m_initial_drive_max_flat_vel, 1.f, 0.f, 100.f);

			ImGui::Text("Drive Max Flat Velocity");
			ImGui::DragFloat("###m_drive_max_flat_velocity", &g_local_player->m_vehicle->m_handling_data->m_drive_max_flat_velocity, 1.f, 0.f, 100.f);


			ImGui::Text("Inertia Multiplier");
			float fInertiaMult[3];
			fInertiaMult[0] = g_local_player->m_vehicle->m_handling_data->m_inertia_mult.x;
			fInertiaMult[1] = g_local_player->m_vehicle->m_handling_data->m_inertia_mult.y;
			fInertiaMult[2] = g_local_player->m_vehicle->m_handling_data->m_inertia_mult.z;
			if (ImGui::SliderFloat3("##inertia_multiplier", fInertiaMult, -10.f, 10.f))
			{
				g_local_player->m_vehicle->m_handling_data->m_inertia_mult.x = fInertiaMult[0];
				g_local_player->m_vehicle->m_handling_data->m_inertia_mult.y = fInertiaMult[1];
				g_local_player->m_vehicle->m_handling_data->m_inertia_mult.z = fInertiaMult[2];
			}

			ImGui::EndTabItem();
		}
	}
};