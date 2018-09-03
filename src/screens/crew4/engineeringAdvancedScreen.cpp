#include "gameGlobalInfo.h"
#include "engineeringAdvancedScreen.h"

#include "screenComponents/beamFrequencySelector.h"
#include "screenComponents/beamTargetSelector.h"
#include "screenComponents/powerDamageIndicator.h"
#include "screenComponents/shieldFreqencySelect.h"
#include "screenComponents/shieldsEnableButton.h"
#include "screenComponents/customShipFunctions.h"

#include "gui/gui2_label.h"

EngineeringAdvancedScreen::EngineeringAdvancedScreen(GuiContainer* owner)
: EngineeringScreen(owner, engineeringAdvanced)
{
    if (gameGlobalInfo->use_beam_shield_frequencies || gameGlobalInfo->use_system_damage)
    {
        GuiElement* beam_info_box = new GuiElement(this, "BEAM_INFO_BOX");
        beam_info_box->setPosition(-20, 170, ATopRight)->setSize(280, 120);
        (new GuiLabel(beam_info_box, "BEAM_INFO_LABEL", "Beam info", 30))->addBackground()->setSize(GuiElement::GuiSizeMax, 40);
        (new GuiPowerDamageIndicator(beam_info_box, "", SYS_BeamWeapons, ACenterLeft))->setSize(GuiElement::GuiSizeMax, 40);
        (new GuiBeamTargetSelector(beam_info_box, "BEAM_TARGET_SELECTOR"))->setPosition(0, 40, ATopRight)->setSize(GuiElement::GuiSizeMax, 40);

        if (!gameGlobalInfo->use_system_damage)
        {
            //If we have shield frequencies but not per system damage, the beam target selector above will not show.
            (new GuiBeamFrequencySelector(beam_info_box, "BEAM_FREQUENCY_SELECTOR"))->setPosition(0, 40, ATopRight)->setSize(GuiElement::GuiSizeMax, 40);
        }else{
            //If we have both shield frequencies and per system damage, move the beam configuration up a bit.
            beam_info_box->setPosition(-20, 130, ATopRight);
            (new GuiBeamFrequencySelector(beam_info_box, "BEAM_FREQUENCY_SELECTOR"))->setPosition(0, 80, ATopRight)->setSize(GuiElement::GuiSizeMax, 40);
        }

        custom_functions->setPosition(20, 360, ATopLeft);
    }

    //The shield frequency selection includes a shield enable button.
    if (gameGlobalInfo->use_beam_shield_frequencies)
        (new GuiShieldFrequencySelect(this, "SHIELD_FREQ"))->setPosition(-20, 250, ATopRight)->setSize(280, 80);
    else if (gameGlobalInfo->use_system_damage)
        (new GuiShieldsEnableButton(this, "SHIELDS_ENABLE"))->setPosition(-20, 210, ATopRight)->setSize(280, 40);
    else
        (new GuiShieldsEnableButton(this, "SHIELDS_ENABLE"))->setPosition(20, 360, ATopLeft)->setSize(240, 50);
}
