#include "pch.h"
#include "arch.h"
#include <shlobj_core.h>
#include <wil/resource.h>

#include "Pages.FramelessPage.h"
#include "Pages.WelcomePage.h"
#if __has_include("Pages.WelcomePage.g.cpp")
#include "Pages.WelcomePage.g.cpp"
#endif

#include "appinfo.hpp"
#include "../ProgramLog/error/win32.hpp"
#include "win32.hpp"

using namespace winrt;
using namespace winrt::Windows::UI::Xaml;

namespace winrt::TranslucentTB::Xaml::Pages::implementation
{
	WelcomePage::WelcomePage(hstring configFile) : m_ConfigFile(std::move(configFile))
	{
		InitializeComponent();
		Title(L"Welcome to " APP_NAME L"!");
	}

	void WelcomePage::ForwardActionClick(const Windows::Foundation::IInspectable &sender, const Windows::UI::Xaml::Controls::ItemClickEventArgs &args)
	{
		args.ClickedItem().as<Models::ActionItem>().ForwardClick(sender, args);
	}

	void WelcomePage::OpenLiberapayLink(const IInspectable &sender, const RoutedEventArgs &args)
	{
		HresultVerify(win32::OpenLink(L"https://liberapay.com/" APP_NAME), spdlog::level::err, L"Failed to open browser");
	}

	void WelcomePage::OpenDiscordLink(const IInspectable &sender, const RoutedEventArgs &args)
	{
		// TODO: try directly opening an installed discord client?
		HresultVerify(win32::OpenLink(L"https://discord.gg/w95DGTK"), spdlog::level::err, L"Failed to open browser");
	}

	void WelcomePage::EditConfigFile(const IInspectable &sender, const RoutedEventArgs &args)
	{
		HresultVerify(win32::EditFile(std::wstring_view(m_ConfigFile)), spdlog::level::err, L"Failed to open text editor");
	}
}
