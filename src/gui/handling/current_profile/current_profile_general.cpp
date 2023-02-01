#include "current_profile_tabs.hpp"

namespace big
{
	void tab_current_profile::tab_general()
	{
		if (ImGui::BeginTabItem("General"))
		{
			ImGui::Text("Gravity");
			ImGui::SliderFloat("##Gravity", &g_local_player->m_vehicle->m_gravity, -50.f, 50.f);


			ImGui::Text("Centre of mass");
			float fCenterOfMass[3]
			{
				g_local_player->m_vehicle->m_handling_data->m_centre_of_mass.x,
				g_local_player->m_vehicle->m_handling_data->m_centre_of_mass.y,
				g_local_player->m_vehicle->m_handling_data->m_centre_of_mass.z
			};
			if (ImGui::SliderFloat3("##centre_of_mass", fCenterOfMass, -10.f, 10.f))
			{
				g_local_player->m_vehicle->m_handling_data->m_centre_of_mass.x = fCenterOfMass[0];
				g_local_player->m_vehicle->m_handling_data->m_centre_of_mass.y = fCenterOfMass[1];
				g_local_player->m_vehicle->m_handling_data->m_centre_of_mass.z = fCenterOfMass[2];
			}

			ImGui::EndTabItem();
		}
	}
}