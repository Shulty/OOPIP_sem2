#include "LabsMenu.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ arg) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    LabsMenu::LabsMenu form;
    Application::Run(% form);
}

