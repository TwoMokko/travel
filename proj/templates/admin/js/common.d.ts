declare namespace Admin {
    namespace Common {
        class Layout extends Base.Common.Layout {
            static header: Base.Common.Section;
            static menu: Base.Common.Section;
            static main: Base.Common.Section;
            static footer: Base.Common.Section;
            static Initialization(): void;
        }
    }
}
