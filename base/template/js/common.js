"use strict";
var Base;
(function (Base) {
    let Common;
    (function (Common) {
        class GlobalParams {
            static param = {};
            static Set(name, value) {
                GlobalParams.param[name] = value;
            }
            static Get(name) {
                return GlobalParams.param[name];
            }
        }
        Common.GlobalParams = GlobalParams;
        class Query {
            static SendData(address, data, handler, params) {
                let method = 'post';
                let request = GlobalParams.Get('request');
                let contentType = 'application/x-www-form-urlencoded;charset=UTF-8';
                let processData = true;
                if (params) {
                    if (params.method)
                        method = params.method;
                    if (params.request !== undefined)
                        request = params.request;
                    if (params.contentType !== undefined)
                        contentType = params.contentType;
                    if (params.processData !== undefined)
                        processData = params.processData;
                }
                $.ajax({
                    url: `${request}${address}`,
                    method: method,
                    dataType: 'json',
                    data: data,
                    contentType: contentType,
                    processData: processData,
                    cache: false,
                    // beforeSend: function() { if (funcBeforeSend) funcBeforeSend(); },
                    // complete: function() { if (funcComplete) funcComplete(); },
                    success: function (response) { Query.Response(response, (handler) ? handler : null); },
                    error: function (response) { console.log('request failed: ' + address); console.log(response); }
                });
            }
            static Send(address, handler, params) {
                Query.SendData(address, {}, handler, params);
            }
            static SendForm(form, handler) {
                let _form = form[0];
                Query.SendData(form.attr('action'), new FormData(_form), handler, { contentType: false, processData: false });
            }
            static SubmitForm(th, handler) {
                Query.SendForm($(th).closest('form'), handler);
            }
            static SubmitFormEvent(e, handler) {
                Query.SendForm($(e.currentTarget).closest('form'), handler);
            }
            static Response(response, handler) {
                switch (response['state']) {
                    case 'ok':
                        if (handler)
                            handler(response['data']);
                        break;
                }
            }
        }
        Common.Query = Query;
        class Section {
            $_elem;
            constructor($_elem) {
                this.$_elem = $_elem;
            }
            Fill(...contents) {
                this.$_elem.empty();
                for (let i in contents) {
                    if (Array.isArray(contents[i]))
                        for (let j in contents[i])
                            this.$_elem.append(contents[i][j]);
                    else
                        this.$_elem.append(contents[i]);
                }
            }
            Push(...contents) {
                for (let i in arguments) {
                    if (Array.isArray(arguments[i]))
                        for (let j in arguments[i])
                            this.$_elem.append(arguments[i][j]);
                    else
                        this.$_elem.append(arguments[i]);
                }
            }
        }
        Common.Section = Section;
        class Layout {
            static Initialization() { }
        }
        Common.Layout = Layout;
    })(Common = Base.Common || (Base.Common = {}));
})(Base || (Base = {}));
//# sourceMappingURL=common.js.map