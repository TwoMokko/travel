"use strict";
var Base;
(function (Base) {
    let Common;
    (function (Common) {
        class Debugger {
            static iter;
            static open;
            static data;
            static dataActive;
            static spaces;
            static spaceActive;
            static record;
            static track;
            static $receiver;
            static $container;
            static $manager;
            static $toggle;
            static $setting;
            static $s_record;
            static $s_track;
            static $s_clear;
            static $work;
            static $drag;
            static $spaces;
            static $panel;
            static $btns = {
                network: null,
                post: null,
                get: null,
                files: null,
                variables: null,
                queries: null,
                controllers: null,
                models: null,
                timestamps: null,
                user: null
            };
            static Initialization() {
                Debugger.iter = 1;
                Debugger.open = (localStorage.getItem('debug_open') === '1');
                Debugger.data = {};
                Debugger.dataActive = 0;
                Debugger.spaceActive = '';
                Debugger.record = (localStorage.getItem('debug_record') !== '0');
                Debugger.track = (localStorage.getItem('debug_track') !== '0');
                Debugger.$receiver = document.body;
                Debugger.$container = document.createElement('div');
                Debugger.$manager = document.createElement('div');
                Debugger.$toggle = document.createElement('div');
                Debugger.$setting = document.createElement('div');
                Debugger.$s_record = document.createElement('a');
                Debugger.$s_track = document.createElement('a');
                Debugger.$s_clear = document.createElement('a');
                Debugger.$work = document.createElement('div');
                Debugger.$drag = document.createElement('div');
                Debugger.$spaces = document.createElement('div');
                Debugger.$panel = document.createElement('div');
                Debugger.$btns.network = document.createElement('a');
                Debugger.$btns.post = document.createElement('a');
                Debugger.$btns.get = document.createElement('a');
                Debugger.$btns.files = document.createElement('a');
                Debugger.$btns.variables = document.createElement('a');
                Debugger.$btns.queries = document.createElement('a');
                Debugger.$btns.controllers = document.createElement('a');
                Debugger.$btns.models = document.createElement('a');
                Debugger.$btns.timestamps = document.createElement('a');
                Debugger.$btns.user = document.createElement('a');
                Debugger.$container.className = 'debugger';
                Debugger.$manager.className = 'manager';
                Debugger.$toggle.className = 'toggle';
                Debugger.$setting.className = 'setting';
                Debugger.$s_record.className = 'record';
                Debugger.$s_track.className = 'track';
                Debugger.$s_clear.className = 'clear';
                Debugger.$work.className = 'work hide';
                Debugger.$drag.className = 'drag';
                Debugger.$spaces.className = 'spaces';
                Debugger.$panel.className = 'panel';
                if (Debugger.record)
                    Debugger.$s_record.classList.add('active');
                if (Debugger.track)
                    Debugger.$s_track.classList.add('active');
                Debugger.$btns.network.innerText = 'Сеть';
                Debugger.$btns.post.innerText = 'POST';
                Debugger.$btns.get.innerText = 'GET';
                Debugger.$btns.files.innerText = 'FILES';
                Debugger.$btns.variables.innerText = 'Переменные';
                Debugger.$btns.queries.innerText = 'Запросы';
                Debugger.$btns.controllers.innerText = 'Контроллеры';
                Debugger.$btns.models.innerText = 'Модели';
                Debugger.$btns.timestamps.innerText = 'Отметки времени';
                Debugger.$btns.user.innerText = 'Пользователь';
                Debugger.$receiver.append(Debugger.$container);
                Debugger.$container.append(Debugger.$manager, Debugger.$work);
                Debugger.$manager.append(Debugger.$toggle, Debugger.$setting);
                Debugger.$setting.append(Debugger.$s_record, Debugger.$s_track, Debugger.$s_clear);
                Debugger.$work.append(Debugger.$drag, Debugger.$spaces, Debugger.$panel);
                Debugger.$panel.append(Debugger.$btns.network, Debugger.$btns.post, Debugger.$btns.get, Debugger.$btns.files, Debugger.$btns.variables, Debugger.$btns.queries, Debugger.$btns.controllers, Debugger.$btns.models, Debugger.$btns.timestamps, Debugger.$btns.user);
                Debugger.$toggle.addEventListener('click', Debugger.ToggleSpase);
                Debugger.$s_record.addEventListener('click', Debugger.ToggleRecord);
                Debugger.$s_track.addEventListener('click', Debugger.ToggleTrack);
                this.$btns.network.addEventListener('click', () => Debugger.OpenSpace('network'));
                this.$btns.post.addEventListener('click', () => this.OpenSpace('post'));
                this.$btns.get.addEventListener('click', () => this.OpenSpace('get'));
                this.$btns.files.addEventListener('click', () => this.OpenSpace('files'));
                this.$btns.variables.addEventListener('click', () => this.OpenSpace('variables'));
                this.$btns.queries.addEventListener('click', () => Debugger.OpenSpace('queries'));
                this.$btns.controllers.addEventListener('click', () => Debugger.OpenSpace('controllers'));
                this.$btns.models.addEventListener('click', () => Debugger.OpenSpace('models'));
                this.$btns.timestamps.addEventListener('click', () => Debugger.OpenSpace('timestamps'));
                this.$btns.user.addEventListener('click', () => Debugger.OpenSpace('user'));
                Debugger.$s_clear.addEventListener('click', () => Debugger.ClearAll());
                Debugger.$drag.onpointerdown = event => {
                    Debugger.$drag.setPointerCapture(event.pointerId);
                    let clientYDown = event.clientY;
                    let heightDown = Debugger.$spaces.offsetHeight;
                    let maxHeight = 500;
                    let minHeight = 100;
                    Debugger.$drag.onpointermove = event => {
                        let alpha = clientYDown - event.clientY;
                        let height = heightDown + alpha;
                        if (height < minHeight)
                            height = minHeight;
                        if (height > maxHeight)
                            height = maxHeight;
                        Debugger.$spaces.style.height = `${height}px`;
                    };
                    Debugger.$drag.onpointerup = () => {
                        localStorage.setItem('debug_height', parseInt(Debugger.$spaces.style.height).toString());
                        Debugger.$drag.onpointermove = null;
                        Debugger.$drag.onpointerup = null;
                    };
                };
                Debugger.spaces = {
                    network: new SNetwork(Debugger.$spaces),
                    post: new SVariables(Debugger.$spaces),
                    get: new SVariables(Debugger.$spaces),
                    files: new SVariables(Debugger.$spaces),
                    variables: new SVariables(Debugger.$spaces),
                    queries: new SQueries(Debugger.$spaces),
                    controllers: new SControllers(Debugger.$spaces),
                    models: new SModels(Debugger.$spaces),
                    timestamps: new STimestamps(Debugger.$spaces),
                    user: new SUser(Debugger.$spaces)
                };
                this.OpenSpace(localStorage.getItem('debug_open_space') || 'network');
                let debug_height = localStorage.getItem('debug_height');
                this.$spaces.style.height = debug_height ? `${debug_height}px` : `200px`;
                if (Debugger.open)
                    Debugger.$work.classList.remove('hide');
            }
            static Append(data) {
                if (!Debugger.record)
                    return;
                Debugger.data[Debugger.iter] = data;
                Debugger.spaces['network'].Set(data['network'], Debugger.iter);
                if (Debugger.track)
                    Debugger.Load(Debugger.iter);
                Debugger.iter++;
            }
            static Load(iter) {
                Debugger.spaces['post'].Clear().Set(Debugger.data[iter]['post']);
                Debugger.spaces['get'].Clear().Set(Debugger.data[iter]['get']);
                Debugger.spaces['files'].Clear().Set(Debugger.data[iter]['files']);
                Debugger.spaces['variables'].Clear().Set(Debugger.data[iter]['variables']);
                Debugger.spaces['queries'].Clear().Set(Debugger.data[iter]['queries']);
                Debugger.spaces['controllers'].Clear().Set(Debugger.data[iter]['controllers']);
                Debugger.spaces['models'].Clear().Set(Debugger.data[iter]['models']);
                Debugger.spaces['timestamps'].Clear().Set(Debugger.data[iter]['timestamps']);
                Debugger.spaces['user'].Clear().Set(Debugger.data[iter]['user']);
            }
            static ToggleSpase() {
                Debugger.open = !Debugger.open;
                localStorage.setItem('debug_open', Debugger.open ? '1' : '0');
                Debugger.open ? Debugger.$work.classList.remove('hide') : Debugger.$work.classList.add('hide');
            }
            static ToggleRecord() {
                Debugger.record = !Debugger.record;
                localStorage.setItem('debug_record', Debugger.record ? '1' : '0');
                Debugger.record ? Debugger.$s_record.classList.add('active') : Debugger.$s_record.classList.remove('active');
            }
            static ToggleTrack() {
                Debugger.track = !Debugger.track;
                localStorage.setItem('debug_track', Debugger.track ? '1' : '0');
                Debugger.track ? Debugger.$s_track.classList.add('active') : Debugger.$s_track.classList.remove('active');
            }
            static OpenSpace(name) {
                if (name === this.spaceActive)
                    return;
                if (this.spaceActive) {
                    this.$btns[this.spaceActive].classList.remove('active');
                    this.spaces[this.spaceActive].Hide();
                }
                this.$btns[name].classList.add('active');
                this.spaces[name].Show();
                this.spaceActive = name;
                localStorage.setItem('debug_open_space', name);
            }
            static ClearAll() {
                Debugger.spaces['network'].Clear();
                Debugger.spaces['post'].Clear();
                Debugger.spaces['get'].Clear();
                Debugger.spaces['files'].Clear();
                Debugger.spaces['variables'].Clear();
                Debugger.spaces['queries'].Clear();
                Debugger.spaces['controllers'].Clear();
                Debugger.spaces['models'].Clear();
                Debugger.spaces['timestamps'].Clear();
                Debugger.spaces['user'].Clear();
                Debugger.data = {};
                Debugger.iter = 1;
            }
        }
        Common.Debugger = Debugger;
        class Space {
            $space;
            constructor($spaces) {
                this.$space = document.createElement('div');
                this.Hide();
                $spaces.append(this.$space);
            }
            PrepareData(data) { return data; }
            Hide() { this.$space.classList.add('hide'); }
            Show() { this.$space.classList.remove('hide'); }
        }
        class STable extends Space {
            cols;
            $wrap;
            $head;
            constructor($spaces, cols) {
                super($spaces);
                this.cols = cols;
                this.$wrap = document.createElement('div');
                this.$head = document.createElement('div');
                this.$wrap.classList.add('table');
                this.$head.classList.add('head');
                this.$space.append(this.$wrap);
                this.$wrap.append(this.$head);
                for (const col in this.cols)
                    this.$head.append(this.GetItem(this.cols[col]));
            }
            GetItem(text) {
                let $item = document.createElement('div');
                $item.innerText = text;
                return $item;
            }
            Set(data, iter) {
                let prepareData = this.PrepareData(data);
                for (const i in prepareData) {
                    let $line = document.createElement('div');
                    $line.classList.add('line');
                    this.$wrap.append($line);
                    for (const col in this.cols)
                        $line.append(this.GetItem(prepareData[i][col]));
                }
            }
            Clear() {
                let elements = this.$wrap.getElementsByClassName('line');
                while (elements.length)
                    elements[0].parentNode.removeChild(elements[0]);
                return this;
            }
        }
        class SNetwork extends STable {
            constructor($spaces) {
                super($spaces, { 'area': 'Страница', 'part': 'Действие', 'point': 'Точка входа', 'type': 'Тип', 'href': 'URL', 'ip': 'IP' });
            }
            Set(data, iter) {
                let $line = document.createElement('div');
                $line.classList.add('line', 'link');
                this.$wrap.append($line);
                for (const col in this.cols)
                    $line.append(this.GetItem(data[col]));
                $line.addEventListener('click', () => { Debugger.Load(iter); });
            }
        }
        class SControllers extends STable {
            constructor($spaces) {
                super($spaces, { 'name': 'Имя', 'file': 'Файл' });
            }
        }
        class SModels extends STable {
            constructor($spaces) {
                super($spaces, { 'name': 'Имя', 'file': 'Файл' });
            }
        }
        class SQueries extends STable {
            constructor($spaces) {
                super($spaces, { 'number': '№', 'query': 'Запрос' });
            }
            PrepareData(data) {
                let out = [];
                for (const i in data)
                    out.push({ 'number': Number(i) + 1, 'query': data[i] });
                return out;
            }
        }
        class STimestamps extends STable {
            constructor($spaces) {
                super($spaces, { 'name': 'Имя', 'time': 'Время (мс.)', 'start': 'Начало', 'stop': 'Конец' });
            }
        }
        class SUser extends STable {
            constructor($spaces) {
                super($spaces, { 'param': 'Параметр', 'value': 'Значение' });
            }
            PrepareData(data) {
                return [{ 'param': 'Имя', 'value': data['name'] }];
            }
        }
        class SVariables extends Space {
            constructor($spaces) {
                super($spaces);
            }
            Set(data) {
                for (const datum of data) {
                    let $dump = document.createElement('div');
                    let $title = document.createElement('div');
                    let $content = document.createElement('div');
                    $dump.classList.add('dump');
                    $title.classList.add('title');
                    $content.classList.add('content');
                    $title.innerText = datum['title'];
                    $content.append(this.Parsing(datum['var']));
                    $dump.append($title, $content);
                    this.$space.append($dump);
                }
            }
            Clear() {
                this.$space.innerText = '';
                return this;
            }
            Parsing(data) {
                let $var = document.createElement('div');
                let $type = document.createElement('div');
                let $value = document.createElement('div');
                $var.classList.add('variable', data['type']);
                $type.classList.add('type');
                $value.classList.add('value');
                $type.innerText = data['type'];
                switch (data['type']) {
                    case 'integer':
                    case 'double':
                        $value.innerText = data['value'].toString();
                        break;
                    case 'string':
                        $value.innerText = data['value'];
                        break;
                    case 'null':
                        $value.innerText = 'null';
                        break;
                    case 'array':
                        $value.append(this.GetArray(data['value']));
                        break;
                    case 'object':
                        $value.append(this.GetObject(data['value']));
                        break;
                }
                $var.append($type, $value);
                return $var;
            }
            GetArray(elems) {
                let $collection = document.createDocumentFragment();
                let $more = document.createElement('div');
                let $elems = document.createElement('div');
                $more.classList.add('more');
                $elems.classList.add('elems');
                $more.addEventListener('click', () => { $more.classList.toggle('open'); });
                $collection.append($more, $elems);
                for (const elem of elems) {
                    let $elem = document.createElement('div');
                    let $key = document.createElement('div');
                    let $index = document.createElement('span');
                    let $value = document.createElement('div');
                    $key.classList.add('key');
                    $value.classList.add('value');
                    if (elem['key']['type'] == 'string') {
                        $key.classList.add('string');
                        $index.innerText = `'${elem['key']['value']}'`;
                    }
                    else {
                        $key.classList.add('number');
                        $index.innerText = elem['key']['value'].toString();
                    }
                    $key.append(`[ `, $index, ` ]`);
                    $elem.append($key, $value);
                    $value.append(this.Parsing(elem['value']));
                    $elems.append($elem);
                }
                return $collection;
            }
            GetObject(obj) {
                function GetElem(key, value) {
                    let $elem = document.createElement('div');
                    let $icon = document.createElement('div');
                    let $value = document.createElement('div');
                    $elem.classList.add(key);
                    $icon.classList.add('icon');
                    $value.innerText = value;
                    $elem.append($icon, $value);
                    return $elem;
                }
                function GetConstant(constant, $value) {
                    let $elem = document.createElement('div');
                    let $icon = document.createElement('div');
                    let $name = document.createElement('div');
                    $icon.classList.add('icon');
                    $name.classList.add('name');
                    if (constant['modifiers'].includes('public'))
                        $icon.classList.add('public');
                    if (constant['modifiers'].includes('protected'))
                        $icon.classList.add('protected');
                    if (constant['modifiers'].includes('private'))
                        $icon.classList.add('private');
                    if (constant['modifiers'].includes('final'))
                        $icon.classList.add('final');
                    $name.innerText = constant['name'];
                    $elem.append($icon, $name, $value);
                    return $elem;
                }
                function GetProperty(property, $value) {
                    let $elem = document.createElement('div');
                    let $icon = document.createElement('div');
                    let $name = document.createElement('div');
                    $icon.classList.add('icon');
                    $name.classList.add('name');
                    if (property['modifiers'].includes('public'))
                        $icon.classList.add('public');
                    if (property['modifiers'].includes('protected'))
                        $icon.classList.add('protected');
                    if (property['modifiers'].includes('private'))
                        $icon.classList.add('private');
                    if (property['modifiers'].includes('static'))
                        $icon.classList.add('static');
                    if (property['modifiers'].includes('readonly'))
                        $icon.classList.add('readonly');
                    $name.innerText = property['name'];
                    $elem.append($icon, $name, $value);
                    return $elem;
                }
                function GetMethod(method) {
                    let $elem = document.createElement('div');
                    let $icon = document.createElement('div');
                    let $name = document.createElement('div');
                    $icon.classList.add('icon');
                    if (method['modifiers'].includes('public'))
                        $icon.classList.add('public');
                    if (method['modifiers'].includes('protected'))
                        $icon.classList.add('protected');
                    if (method['modifiers'].includes('private'))
                        $icon.classList.add('private');
                    if (method['modifiers'].includes('static'))
                        $icon.classList.add('static');
                    if (method['modifiers'].includes('final'))
                        $icon.classList.add('final');
                    if (method['modifiers'].includes('abstract'))
                        $icon.classList.add('abstract');
                    $name.innerText = method['name'];
                    $elem.append($icon, $name);
                    return $elem;
                }
                let $collection = document.createDocumentFragment();
                let $more = document.createElement('div');
                let $info = document.createElement('div');
                $more.classList.add('more');
                $info.classList.add('info');
                $more.addEventListener('click', () => { $more.classList.toggle('open'); });
                $info.append(GetElem('namespace', obj['namespace']));
                $info.append(GetElem('class', obj['name']));
                let $constants = document.createElement('div');
                $constants.classList.add('constants');
                for (const constant of obj['constants'])
                    $constants.append(GetConstant(constant, this.Parsing(constant['value'])));
                $info.append($constants);
                let $properties = document.createElement('div');
                $properties.classList.add('properties');
                for (const property of obj['properties'])
                    $properties.append(GetProperty(property, this.Parsing(property['value'])));
                $info.append($properties);
                let $methods = document.createElement('div');
                $methods.classList.add('methods');
                for (const method of obj['methods'])
                    $methods.append(GetMethod(method));
                $info.append($methods);
                $collection.append($more, $info);
                return $collection;
            }
        }
    })(Common = Base.Common || (Base.Common = {}));
})(Base || (Base = {}));
function getCookie(name) {
    let matches = document.cookie.match(new RegExp("(?:^|; )" + name.replace(/([\.$?*|{}\(\)\[\]\\\/\+^])/g, '\\$1') + "=([^;]*)"));
    return matches ? decodeURIComponent(matches[1]) : null;
}
function setCookie(name, value, options = {}) {
    options = {
        path: '/',
        ...options
    };
    if (options.expires && options.expires instanceof Date) {
        options.expires = options.expires.toUTCString();
    }
    let updatedCookie = encodeURIComponent(name) + "=" + encodeURIComponent(value);
    for (let optionKey in options) {
        updatedCookie += "; " + optionKey;
        let optionValue = options[optionKey];
        if (optionValue !== true) {
            updatedCookie += "=" + optionValue;
        }
    }
    document.cookie = updatedCookie;
}
function deleteCookie(name) {
    setCookie(name, '', { 'max-age': -1 });
}
function getContent(route = '') {
    let url = new URL(window.location.href);
    let href = url.origin;
    let pathname = route ? url.pathname.replace(route, `${route}/xhr`) : `/xhr${url.pathname}`;
    let params = url.search;
    Base.Common.Query.Send(`${href}${pathname}${params}`, null, { request: '' });
}
var Base;
(function (Base) {
    let Common;
    (function (Common) {
        class History {
            static Initialization() {
                $(window).on('popstate', event => {
                    let state = event.originalEvent.state;
                    if (!state)
                        return;
                    Base.Common.Query.SendData(state.xhr, { no_history: 1 }, state.handler ? eval(state.handler) : null, { request: '' });
                });
            }
            static Replace(address, xhr) {
                window.history.replaceState({ xhr: xhr }, '', address);
            }
        }
        Common.History = History;
    })(Common = Base.Common || (Base.Common = {}));
})(Base || (Base = {}));
var Base;
(function (Base) {
    let Common;
    (function (Common) {
        class Layout {
            static Initialization() { }
        }
        Common.Layout = Layout;
    })(Common = Base.Common || (Base.Common = {}));
})(Base || (Base = {}));
var Base;
(function (Base) {
    let Common;
    (function (Common) {
        class Notice {
            /* Variables */
            static iter = 0;
            static notices = {};
            /* Elements */
            static $notices = null;
            static Create(type, html) {
                return Notice.New(type, html);
            }
            static Ok(html) {
                return Notice.New('ok', html);
            }
            static Info(html) {
                return Notice.New('info', html);
            }
            static Error(html) {
                return Notice.New('error', html);
            }
            static New(type, html) {
                if (!Notice.$notices) {
                    Notice.$notices = $('<div/>', { class: 'view general notices' });
                    $('body').append(Notice.$notices);
                }
                Notice.iter++;
                let _wind = new Instance(Notice.iter, type, html);
                Notice.notices[Notice.iter] = _wind;
                return _wind;
            }
            static Delete(id) {
                delete Notice.notices[id];
            }
        }
        Common.Notice = Notice;
        class Instance {
            /* Variables */
            id;
            /* Elements */
            $instance;
            constructor(id, type, html) {
                this.id = id;
                /* Elements */
                this.$instance = $('<div/>', { class: `instance ${type}` });
                let $notice = $('<div/>', { class: 'notice' });
                let $type = $('<div/>', { class: 'type' });
                let $close = $('<div/>', { class: 'close' });
                /* Building DOM */
                Notice.$notices.prepend(this.$instance.append($type, $notice.append(html), $('<div/>', { class: 'close' }).append($close)));
                /* Events */
                $close.on('click', this.Close.bind(this));
            }
            Close() {
                this.Remove();
            }
            Remove() {
                this.$instance.remove();
                Notice.Delete(this.id);
            }
        }
    })(Common = Base.Common || (Base.Common = {}));
})(Base || (Base = {}));
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
    })(Common = Base.Common || (Base.Common = {}));
})(Base || (Base = {}));
var Base;
(function (Base) {
    let Common;
    (function (Common) {
        class Query {
            static SendData(address, data, handler, params) {
                let method = 'post';
                let request = Common.GlobalParams.Get('xhr');
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
                for (const i in response)
                    Query.Execute(response[i].type, response[i].data, handler);
            }
            static Execute(type, data, handler) {
                switch (type) {
                    case 'history':
                        Query.ExecuteHistory(data);
                        break;
                    case 'section':
                        Query.ExecuteSection(data);
                        break;
                    case 'notice':
                        Query.ExecuteNotice(data);
                        break;
                    case 'data':
                        Query.ExecuteHandler(handler, data);
                        break;
                    case 'debugger':
                        Common.Debugger.Append(data);
                        break;
                }
            }
            static ExecuteHistory(data) {
                window.history.pushState({ xhr: data.xhr, handler: data.handler }, '', data.address);
            }
            static ExecuteSection(data) {
                let $section = $(data.section);
                if (data.empty)
                    $section.empty();
                $section.append(data.html); /*Admin.Common.Layout.main.Fill*/
            }
            static ExecuteNotice(data) {
                Base.Common.Notice.Create(data.type, data.notice);
            }
            static ExecuteHandler(handler, data) {
                if (handler)
                    handler(data);
            }
        }
        Common.Query = Query;
    })(Common = Base.Common || (Base.Common = {}));
})(Base || (Base = {}));
var Base;
(function (Base) {
    let Common;
    (function (Common) {
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
    })(Common = Base.Common || (Base.Common = {}));
})(Base || (Base = {}));
var Base;
(function (Base) {
    let Skins;
    (function (Skins) {
        class Table {
            number;
            name;
            columns;
            $container;
            $table;
            $thead;
            $tr_head;
            $tbody;
            $add;
            constructor(selector, name, columns, values = []) {
                this.number = 0;
                this.name = name;
                this.columns = columns;
                this.$container = $(selector);
                this.$table = $('<table/>');
                this.$thead = $('<thead/>');
                this.$tbody = $('<tbody/>');
                this.$tr_head = $('<tr/>');
                this.$add = $('<input/>', { type: 'button', value: 'добавить' });
                this.$container.append(this.$table.append(this.$thead.append(this.$tr_head), this.$tbody), this.$add);
                for (let i in columns)
                    this.$tr_head.append($('<td/>').text(columns[i].alias));
                this.$tr_head.append($('<td/>').text('удаление'));
                for (let i in values)
                    this.AddColumn(values[i]);
                this.$add.on('click', this.AddColumn.bind(this));
            }
            AddColumn(values = null) {
                this.number++;
                let tr = $('<tr/>');
                this.$tbody.append(tr);
                let $elem = $();
                for (let i in this.columns) {
                    let value = values ? values[this.columns[i].name] : '';
                    switch (this.columns[i].type) {
                        case 'text':
                        case 'number':
                            $elem = this.GetInput(this.columns[i], this.number, value);
                            break;
                        case 'textarea':
                            $elem = this.GetTextarea(this.columns[i], this.number, value);
                            break;
                    }
                    tr.append($('<td/>').append($elem));
                }
                tr.append($('<td/>').append($('<input/>', { type: 'button', value: 'удалить' })).on('click', () => tr.remove()));
            }
            GetInput(params, iter, value = '') {
                return $('<input/>', { type: params.type, name: `${this.name}[${iter}][${params.name}]`, value: value });
            }
            GetTextarea(params, iter, value = '') {
                return $('<textarea/>', { name: `${this.name}[${iter}][${params.name}]`, text: value });
            }
        }
        Skins.Table = Table;
        class UploaderPhoto {
            $wrap;
            $input;
            $space;
            $container;
            path_load;
            path_del;
            path_view;
            constructor(selector, text, path_load, path_del, path_view, photos) {
                this.$wrap = $('<div/>', { class: 'uploader_photo' });
                this.$input = $(selector);
                this.$space = $('<div/>', { class: 'upload_space' });
                this.$container = $('<div/>', { class: 'img_container' });
                this.path_load = path_load;
                this.path_del = path_del;
                this.path_view = path_view;
                this.$input.after(this.$wrap.append(this.$space.text(text), this.$container));
                this.ShowFiles(photos);
                this.$wrap.prepend(this.$input);
                this.$input.on('change', (e) => {
                    this.LoadFiles(e.target.files);
                    this.$input.val('');
                });
                this.$space.on('click', () => {
                    this.$input.trigger('click');
                });
                this.$space.on('dragover', false);
                this.$space.on('dragenter', () => {
                    this.$space.addClass('active');
                });
                this.$space.on('dragleave', () => {
                    this.$space.removeClass('active');
                });
                this.$space.on('drop', e => {
                    this.LoadFiles(e.originalEvent.dataTransfer.files);
                    this.$space.removeClass('active');
                    return false;
                });
            }
            LoadFiles(files) {
                for (let i = 0; i < files.length; i++) {
                    new File(files[i], this.$container, this.path_load, this.path_del);
                }
            }
            ShowFiles(photos) {
                for (let i in photos) {
                    let $image = $('<div/>', { class: 'img' });
                    let $del = $('<div/>', { class: 'delete active' });
                    this.$container.append($image.append($del));
                    $image.css('background-image', `url(${this.path_view}${photos[i].image})`);
                    $del.on('click', () => {
                        Base.Common.Query.SendData(this.path_del, { id: photos[i].id }, () => {
                            $image.remove();
                        }, { request: '' });
                    });
                }
            }
        }
        Skins.UploaderPhoto = UploaderPhoto;
        class File {
            $image;
            $del;
            $wait;
            constructor(file, $container, path_load, path_del) {
                this.$image = $('<div/>', { class: 'img' });
                this.$del = $('<div/>', { class: 'delete' });
                this.$wait = $('<div/>', { class: 'wait active' });
                $container.append(this.$image.append(this.$wait, this.$del));
                let reader = new FileReader();
                reader.onloadend = (e) => {
                    this.$image.css('background-image', `url(${e.target.result})`);
                    let data = new FormData();
                    data.append('file', file);
                    Base.Common.Query.SendData(path_load, data, data => {
                        switch (data['action']) {
                            case 'ok':
                                this.$wait.removeClass('active');
                                this.$del.addClass('active').on('click', () => {
                                    Base.Common.Query.SendData(path_del, data, () => {
                                        this.$image.remove();
                                    }, { request: '' });
                                });
                                break;
                            case 'error': alert(data['text']);
                        }
                    }, { processData: false, contentType: false, request: '' });
                };
                reader.readAsDataURL(file);
            }
        }
    })(Skins = Base.Skins || (Base.Skins = {}));
})(Base || (Base = {}));
//# sourceMappingURL=common.js.map