# --  Display  -----------------------------------------------------------------

include_directories(
	src/display/
	src/display/enums/
	src/display/interface/
	src/display/interface/menus/
	src/display/interface/menus/components/
	src/display/interface/otherWindows/
	src/display/utils/
)

set( ZZ_MAKER_DISPLAY_HEADERS
		src/display/enums/colors.hpp
		src/display/enums/assetsFiles.hpp
		src/display/interface/editor.hpp
		src/display/interface/mainWindow.hpp
		src/display/interface/menus/gameElementSelector.hpp
		src/display/interface/menus/components/gameElement.hpp
		src/display/interface/otherWindows/helpWindow.hpp
		src/display/utils/sprite.hpp
		src/display/interface/menus/gameManager.hpp
		src/display/interface/otherWindows/game_window/mainGameWindow.hpp
		src/display/interface/otherWindows/game_window/game_classes/sfElement.hpp
		src/display/interface/otherWindows/game_window/game_classes/sfEnemy.hpp
		src/display/interface/otherWindows/game_window/game_classes/sfPlayer.hpp
		src/display/interface/otherWindows/closeConfirmationWindow.hpp
		src/display/interface/otherWindows/newConfirmationWindow.hpp
		src/display/interface/otherWindows/openWindow.hpp
		src/display/interface/otherWindows/saveWindow.hpp
		src/display/interface/otherWindows/errorWindow.hpp
		src/display/interface/otherWindows/component/confirmationPanel.hpp
		src/display/interface/otherWindows/component/pathSelector.hpp
		)

set( ZZ_MAKER_DISPLAY_SOURCES
		src/display/enums/colors.cpp
		src/display/enums/assetsFiles.cpp
		src/display/interface/editor.cpp
		src/display/interface/mainWindow.cpp
		src/display/interface/menus/gameElementSelector.cpp
		src/display/interface/menus/components/gameElement.cpp
		src/display/interface/otherWindows/helpWindow.cpp
		src/display/utils/sprite.cpp
		src/display/interface/menus/gameManager.cpp
		src/display/interface/otherWindows/game_window/mainGameWindow.cpp
		src/display/interface/otherWindows/game_window/game_classes/sfElement.cpp
		src/display/interface/otherWindows/game_window/game_classes/sfEnemy.cpp
		src/display/interface/otherWindows/game_window/game_classes/sfPlayer.cpp
		src/display/interface/otherWindows/closeConfirmationWindow.cpp
		src/display/interface/otherWindows/newConfirmationWindow.cpp
		src/display/interface/otherWindows/openWindow.cpp
		src/display/interface/otherWindows/saveWindow.cpp
		src/display/interface/otherWindows/errorWindow.cpp
		src/display/interface/otherWindows/component/confirmationPanel.cpp
		src/display/interface/otherWindows/component/pathSelector.cpp
)
