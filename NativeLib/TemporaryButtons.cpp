#include "TemporaryButtons.h"

void TemporaryButtons::_register_methods()
{
	register_method("_on_CloseAllLevels_pressed", &TemporaryButtons::_on_CloseAllLevels_pressed);
}

void TemporaryButtons::_init()
{

}

void TemporaryButtons::_on_CloseAllLevels_pressed()
{
	for (int i = 0; i < 23; i++)
	{
		Oblast* oblast;
		oblast = cast_to<Oblast>(get_node(NodePath((String)"/root/Node2D/Map/" + String::num(i + 1))));
		oblast->Close();

		DataLoader::GetSingleton()->CloseLevel(i + 1);
	}
}