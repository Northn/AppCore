#include <AppCore/App.h>
#include <AppCore/Window.h>
#include <AppCore/Overlay.h>

using namespace ultralight;

class MyApp : public WindowListener, public ViewListener {
  RefPtr<App> app_;
  RefPtr<Window> window_;
  RefPtr<Overlay> overlay_;
public:
  MyApp() {
    ///
    /// Create our main App instance.
    ///
    app_ = App::Create();

    ///
    /// Create our Window with the Resizable window flag.
    ///
    window_ = Window::Create(app_->main_monitor(), 800, 600, false,
      kWindowFlags_Titled | kWindowFlags_Resizable);

    ///
    /// Set our window title.
    ///
    window_->SetTitle("MiniBrowser");

    ///
    /// Bind our App's main window.
    ///
    /// @note This MUST be done before creating any overlays or calling App::Run
    ///
    app_->set_window(*window_.get());

    ///
    /// Create our Overlay, use the same dimensions as our Window.
    ///
    overlay_ = Overlay::Create(*window_.get(), window_->width(),
      window_->height(), 0, 0);

    ///
    /// Load a string of HTML into our overlay's View
    ///
    //overlay_->view()->LoadURL("file:///ui.html");
    overlay_->view()->LoadURL("https://en.wikipedia.org");

    ///
    /// Register our MyApp instance as a WindowListener so we can handle the
    /// Window's OnResize event below.
    ///
    window_->set_listener(this);

    ///
    /// Register our MyApp instance as a ViewListener so we can handle the
    /// View's OnChangeCursor event below.
    ///
    overlay_->view()->set_view_listener(this);
  }

  virtual ~MyApp() {}

  ///
  /// Inherited from WindowListener, not used.
  ///
  virtual void OnClose() override {}

  ///
  /// Inherited from WindowListener, called when the Window is resized.
  ///
  virtual void OnResize(uint32_t width, uint32_t height) override {
    ///
    /// Resize our Overlay to match the new Window dimensions.
    ///
    overlay_->Resize(width, height);
  }

  ///
  /// Inherited from ViewListener
  ///
  virtual void OnChangeCursor(ultralight::View* caller,
    Cursor cursor) {
    window_->SetCursor(cursor);
  }

  void Run() {
    app_->Run();
  }
};

int main() {
  MyApp app;
  app.Run();

  return 0;
}