#include <Core/Application.h>
#include <GamerServices/GamerServices.h>

using namespace clem;

int main()
{
    GamerServices::init();

    /*
    Application::Config config = {
        .display = {
            .resolution = {100, 100},
        }
    };

    auto& app = Application::get();
    app.setConfig(config);

    auto& win = app.getWindow();
    win.setVisible(true);
    */

    GamerServices::deinit();

    return 0;
}