#include <xtd/xtd.delegates>
#include <iostream>
#include <string>

using namespace std;
using namespace xtd;

struct control {
  const string& text() const {return this->text_;}
  void text(const string& text) {
    if (this->text_ != text) {
      this->text_ = text;
      this->on_text_changed(event_args::empty);
    }
  }
  
  event<control, event_handler<control>> text_changed;
  
  void on_text_changed(const event_args& e) {this->text_changed(*this, e);}
  
private:
  string text_;
};

struct button : public control {
  event<button, event_handler<control>> click;
  
  void perform_click() {this->on_click(event_args::empty);}
  
  virtual void on_click(const event_args& e) {this->click(*this, e);}
};

int main() {
  button button1;
  
  button1.text_changed += [](const control& sender, const event_args& e)  {
    cout << "text_changed [text=" << sender.text() << "]" << endl;
  };
  
  button1.click += []  {
    cout << "click on button" << endl;
  };
  
  button1.text("button1");
  
  // click simulation
  button1.perform_click();
}