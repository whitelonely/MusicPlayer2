﻿#pragma once

class MenuMgr
{
public:
    MenuMgr();
    virtual ~MenuMgr();

    enum MenuType
    {
        MainPopupMenu,                      // 主窗口（弹出菜单ver）（shift+右键）
        MainMenu,                           // 主窗口
        MainFileMenu,                       // 主窗口->子菜单"文件"
        MainPlayCtrlMenu,                   // 主窗口->子菜单"播放控制"
        MainPlayCtrlRepeatModeMenu,         // 主窗口->子菜单"播放控制"->子菜单"循环模式"
        MainPlayCtrlAbRepeatMenu,           // 主窗口->子菜单"播放控制"->子菜单"AB重复"
        MainPlaylistMenu,                   // 主窗口->子菜单"播放列表"
        MainPlaylistAddMenu,                // 主窗口->子菜单"播放列表"->子菜单"添加"          播放列表工具栏->添加(0)
        MainPlaylistDelMenu,                // 主窗口->子菜单"播放列表"->子菜单"删除"          播放列表工具栏->删除(1)
        MainPlaylistSortMenu,               // 主窗口->子菜单"播放列表"->子菜单"排序方式"      播放列表工具栏->排序(2)
        MainPlaylistDispModeMenu,           // 主窗口->子菜单"播放列表"->子菜单"播放列表显示方式"
        MainLyricMenu,                      // 主窗口->子菜单"歌词"
        MainLrcChConvMenu,                  // 主窗口->子菜单"歌词"->子菜单"繁简转换"
        MainLrcInnerLrcMenu,                // 主窗口->子菜单"歌词"->子菜单"内嵌歌词"
        MainViewMenu,                       // 主窗口->子菜单"视图"
        MainViewSwitchUiMenu,               // 主窗口->子菜单"视图"->子菜单"切换界面"
        MainToolMenu,                       // 主窗口->子菜单"工具"
        MainToolCreateShortcutMenu,         // 主窗口->子菜单"工具"->子菜单"创建快捷方式"
        MainToolAlbumCoverMenu,             // 主窗口->子菜单"工具"->子菜单"专辑封面"
        MainToolDelCurPlayingMenu,          // 主窗口->子菜单"工具"->子菜单"删除正在播放的曲目"
        MainHelpMenu,                       // 主窗口->子菜单"帮助"

        PlaylistToolBarMenu,                // 播放列表工具栏(弹出菜单)
        PlaylistToolBarListMenu,            // 播放列表工具栏->列表(3)
        PlaylistToolBarEditMenu,            // 播放列表工具栏->编辑(4)
        PlaylistToolBarFolderMenu,          // 播放列表工具栏->文件夹(5)

        MainAreaMenu,                       // 主界面区域菜单
        MainAreaLrcMenu,                    // 主界面歌词区域菜单(与MainLyricMenu共用翻译)
        MainAreaPlaylistBtnMenu,            // 主界面播放列表按钮
        DlrcMenu,                           // 桌面歌词窗口
        DlrcDefMenu,                        // 桌面歌词窗口->子菜单"预设方案"
        RecentFolderPlaylistMenu,           // MenuEditCtrl控件(最近播放文件夹/播放列表)
        PlaylistMenu,                       // 播放列表菜单
        RateMenu,                           // "分级"菜单
        AddToPlaylistMenu,                  // "添加到播放列表"菜单

        MiniAreaMenu,                       // 迷你模式区域菜单
        MiniModeSwitchUiMenu,               // 迷你模式切换界面菜单
        NotifyMenu,                         // 系统托盘图标

        LibSetPathMenu,                     // 媒体库文件夹标签页菜单
        LibPlaylistMenu,                    // 媒体库播放列表标签页菜单
        LibLeftMenu,                        // 媒体库左侧菜单
        LibRightMenu,                       // 媒体库右侧菜单

        LeMenu,                             // 歌词编辑对话框->窗口菜单
        LeFileMenu,                         // 歌词编辑对话框->窗口菜单->子菜单"文件"
        LeEditMenu,                         // 歌词编辑对话框->窗口菜单->子菜单"编辑"
        LeEditChConvMenu,                   // 歌词编辑对话框->窗口菜单->子菜单"编辑"->子菜单"繁简转换"
        LeEditTagDislocMenu,                // 歌词编辑对话框->窗口菜单->子菜单"编辑"->子菜单"时间标签错位"
        LePlayCtrlMenu,                     // 歌词编辑对话框->窗口菜单->子菜单"播放控制"

        FcListMenu,                         // 转换格式对话框->列表控件
        LdListMenu,                         // 歌词下载对话框->列表控件
        OptDlrcDefStyleMenu,                // 选项设置->歌词设置->预设方案按钮
        OptDlrcModDefStyleMenu,             // 选项设置->歌词设置->预设方案按钮菜单->子菜单"修改预设方案"
        PropertyAdvMenu,                    // 属性对话框->高级标签信息标签页->列表控件
        PropertyCoverMenu,                  // 属性对话框->专辑封面标签页

        MenuMax // 菜单数量
    };
    // 目前只支持更新为关联到命令的普通菜单项(默认构造表示分隔符)
    struct MenuItem
    {
        UINT id{ NULL };
        HICON hicon{ NULL };
        wstring text;
    };
    // 更新菜单项
    void UpdateMenu(MenuType menu_type, const vector<MenuItem>& items);
    // 获取菜单句柄
    HMENU GetSafeHmenu(MenuType menu_type);
    // 获取CMenu指针
    CMenu* GetMenu(MenuType menu_type);

private:
    struct MenuBase
    {
        MenuBase(MenuMgr* pMenuMgr, MenuType menu_type);
        ~MenuBase();

        void CreateMenu(bool is_popup, bool add_accelerator);
        void AppendItem(UINT wID, const wstring& id_text, HICON hicon, const wchar_t* text = nullptr);  // 可变参数列表宏至少要一个参数，所以hicon不能预设NULL，不使用时请指定NULL
        void AppendSubMenu(MenuType menu_type, HICON hicon);
        void AppendSeparator();
        void SetUpdatePos() { m_update_pos = m_end_pos; }
        void SetDefaultItem();

        MenuType GetMenuType() const { return m_menu_type; }
        void UpdateMenu(const vector<MenuItem>& items);

        CMenu m_menu;
    private:
        MenuMgr* m_pMenuMgr;
        MenuType m_menu_type;
        int m_end_pos{ 0 };
        int m_update_pos{ -1 };
        bool m_add_accelerator{ false };                // AppendItem是否自动根据命令ID附加加速键列表中的快捷键文本
    };

    MenuBase& GetMenuBase(MenuType menu_type);

    static const wchar_t* GetMenuNameStr(MenuType menu_type);
    static void CreateMenu(MenuBase& menu_base);
private:
    std::unique_ptr<MenuBase> m_menus[MenuMax];
};

