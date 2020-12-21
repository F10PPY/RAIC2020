TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += "ENABLE_VW"
#DEFINES +="LOCAL_DBG"

LIBS+=  -lfreetype -lglfw3 -lGL -lX11 -ldl -lpthread

SOURCES += \
DebugInterface.cpp \
MyStrategy.cpp \
Stream.cpp \
TcpStream.cpp \
	ai/ai_api_actions.cpp \
	ai/ai_building.cpp \
	ai/ai_manager_main.cpp \
	ai/ai_outdated.cpp \
	ai/ai_pfs.cpp \
	ai/ai_repairing.cpp \
	ai/ai_update.cpp \
main.cpp \
model/Action.cpp \
model/AttackAction.cpp \
model/AttackProperties.cpp \
model/AutoAttack.cpp \
model/BuildAction.cpp \
model/BuildProperties.cpp \
model/Camera.cpp \
model/ClientMessage.cpp \
model/Color.cpp \
model/ColoredVertex.cpp \
model/DebugCommand.cpp \
model/DebugData.cpp \
model/DebugState.cpp \
model/Entity.cpp \
model/EntityAction.cpp \
model/EntityProperties.cpp \
model/MoveAction.cpp \
model/Player.cpp \
model/PlayerView.cpp \
model/RepairAction.cpp \
model/RepairProperties.cpp \
model/ServerMessage.cpp \
model/Vec2Float.cpp \
model/Vec2Int.cpp \
../../glad/src/glad.c \
vw.cpp \
vw_callbacks.cpp \
vw_render_loop.cpp \
../../imgui-master/backends/imgui_impl_glfw.cpp \
../../imgui-master/backends/imgui_impl_opengl3.cpp \
../../imgui-master/imgui.cpp \
../../imgui-master/imgui_demo.cpp \
../../imgui-master/imgui_draw.cpp \
../../imgui-master/imgui_widgets.cpp \
	vw_render_text.cpp

INCLUDEPATH+= ../../imgui-master/ \
../../imgui-master/backends/ \
../../glad/include/glad/ \
../../ \
deps/ \
/usr/include/freetype2/ \
ai/ \

HEADERS += \
DebugInterface.hpp \
MyStrategy.hpp \
Stream.hpp \
TcpStream.hpp \
ai/ai.h \
model/Action.hpp \
model/AttackAction.hpp \
model/AttackProperties.hpp \
model/AutoAttack.hpp \
model/BuildAction.hpp \
model/BuildProperties.hpp \
model/Camera.hpp \
model/ClientMessage.hpp \
model/Color.hpp \
model/ColoredVertex.hpp \
model/DebugCommand.hpp \
model/DebugData.hpp \
model/DebugState.hpp \
model/Entity.hpp \
model/EntityAction.hpp \
model/EntityProperties.hpp \
model/EntityType.hpp \
model/Model.hpp \
model/MoveAction.hpp \
model/Player.hpp \
model/PlayerView.hpp \
model/PrimitiveType.hpp \
model/RepairAction.hpp \
model/RepairProperties.hpp \
model/ServerMessage.hpp \
model/Vec2Float.hpp \
model/Vec2Int.hpp \
vw.h \
vw_shaders.h \
ntb_util.h


DISTFILES += \
CMakeLists.txt
