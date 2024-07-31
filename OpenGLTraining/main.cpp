#include "core/Render.h"

int main()
{
    hiveWindow::CRender::getInstance().startup("Window.xml", "DeferredShading.xml");
    hiveWindow::CRender::getInstance().run();
    return 0;
}