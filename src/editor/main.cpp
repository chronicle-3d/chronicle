// #include <MainWindow.h>

#include <Chronicle.h>
#include <cstdlib>

int main(int argc, char **argv)
{
    // spdlog::set_level(spdlog::level::debug);
    // try {
    //     chronicle::editor::MainWindow window {};
    //     window.run();
    // } catch (const std::exception& e) {
    //     CHRLOG_ERROR("Unhandled exception: {}", e.what());
    //     return EXIT_FAILURE;
    // }

    chronicle::Chronicle::Init();
    chronicle::Chronicle::Run();
    chronicle::Chronicle::Deinit();

    return EXIT_SUCCESS;
}