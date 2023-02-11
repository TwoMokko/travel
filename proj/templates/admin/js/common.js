"use strict";
var Admin;
(function (Admin) {
    let Common;
    (function (Common) {
        class Layout extends Base.Common.Layout {
            static header;
            static menu;
            static main;
            static footer;
            static Initialization() {
                Layout.header = new Base.Common.Section($('header'));
                Layout.menu = new Base.Common.Section($('menu'));
                Layout.main = new Base.Common.Section($('main'));
                Layout.footer = new Base.Common.Section($('footer'));
            }
        }
        Common.Layout = Layout;
    })(Common = Admin.Common || (Admin.Common = {}));
})(Admin || (Admin = {}));
//# sourceMappingURL=common.js.map