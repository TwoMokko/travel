"use strict";
var Admin;
(function (Admin) {
    let General;
    (function (General) {
        class Render {
            static ToMain(data) {
                if (data['message'])
                    alert(data['message']);
                Admin.Common.Layout.main.Fill(data['html']);
            }
            static CheckDB(data) {
                Admin.Common.Layout.main.Fill($('<h1/>').text('Проверка базы данных'), data.length ? Render.Form(data) : Render.Empty());
            }
            static Form(data) {
                /* Elements */
                let $form = $('<form/>', { action: '/db/make' }); //TODO Разработать систему экшинов
                let $table = $('<table/>', { class: 'select' });
                let $tbody = $('<tbody/>');
                let $checkbox = $('<input/>', { type: 'checkbox' });
                let $submit = $('<input/>', { type: 'submit', value: 'Исправить' });
                /* Handlers */
                let OnSelectAll = () => {
                    $('table input[type="checkbox"]').prop('checked', $checkbox.is(':checked'));
                };
                let OnSubmit = (e) => {
                    Base.Common.Query.SubmitFormEvent(e, function (data) {
                        Admin.General.Render.CheckDB(data);
                    });
                    return false;
                };
                /* Events */
                $checkbox.on('click', OnSelectAll);
                $submit.on('click', OnSubmit);
                /* Building DOM */
                $form.append($table.append($('<thead/>').append($('<tr/>').append($('<th/>').text('Таблица'), $('<th/>').text('Поле'), $('<th/>').append($checkbox), $('<th/>').text('Ошибка'))), $tbody), $submit);
                Render.Tables($tbody, data);
                return $form;
            }
            static Tables($tbody, tables) {
                for (let i in tables)
                    Render.Table($tbody, tables[i]);
            }
            static Table($tbody, table) {
                /* Elements */
                let $checkbox = $('<input/>', { type: 'checkbox', name: `tables[${table.name}][action]`, value: table.action });
                /* Handlers */
                let OnSelectTable = () => {
                    $(`input[name^="tables[${table.name}]["]`).prop('checked', $checkbox.is(':checked'));
                };
                /* Events */
                $checkbox.on('click', OnSelectTable);
                /* Building DOM */
                $tbody.append($('<tr/>').append($('<td/>').text(table.name), $('<td/>').text('-'), $('<td/>').append($checkbox), $('<td/>').text(table.error)));
                if (table.fields)
                    Render.Fields($tbody, table.name, table.fields);
            }
            static Fields($tbody, tablename, fields) {
                for (let i in fields)
                    Render.Field($tbody, tablename, fields[i]);
            }
            static Field($tbody, tablename, field) {
                /* Elements */
                let $checkbox = $('<input/>', { type: 'checkbox', name: `tables[${tablename}][fields][${field.name}][action]`, value: field.action });
                let textError = field.error + ((field.details) ? ` (${field.details})` : '');
                /* Handlers */
                let OnSelectField = () => {
                    if ($checkbox.is(':checked'))
                        $(`input[name^="tables[${tablename}][action]"]`).prop('checked', true);
                };
                /* Events */
                $checkbox.on('click', OnSelectField);
                /* Building DOM */
                $tbody.append($('<tr/>').append($('<td/>').text(tablename), $('<td/>').text(field.name), $('<td/>').append($checkbox), $('<td/>').text(textError)));
            }
            static Empty() {
                return $('<h3>').text('База данных исправна.');
            }
        }
        General.Render = Render;
        class Structure {
            static displayNames = 1;
            static displayDescriptions = 2;
            db;
            displayMode;
            $topElement;
            $structure;
            $panel;
            $display;
            constructor(data) {
                this.displayMode = Structure.displayDescriptions;
                this.$structure = document.getElementById('structure');
                this.db = new DB(data, this.$structure, this);
                this.RenderPanel();
            }
            RenderPanel() {
                this.$panel = document.createElement('div');
                this.$panel.className = 'panel';
                this.$display = document.createElement('a');
                this.$display.className = 'display';
                this.$structure.className = (this.displayMode === Structure.displayNames) ? 'display_name' : 'display_description';
                this.$display.addEventListener('click', () => this.SwitchDisplayMode());
                this.$structure.append(this.$panel);
                this.$panel.append(this.$display);
            }
            SwitchDisplayMode() {
                if (this.displayMode === Structure.displayNames) {
                    this.displayMode = Structure.displayDescriptions;
                    this.$structure.className = 'display_description';
                }
                else {
                    this.displayMode = Structure.displayNames;
                    this.$structure.className = 'display_name';
                }
            }
            HoverElement($elem) {
                if (this.$topElement)
                    this.$topElement.style.zIndex = '0';
                $elem.style.zIndex = '1';
                this.$topElement = $elem;
            }
        }
        General.Structure = Structure;
        class DB {
            tables;
            activeKey;
            constructor(data, $structure, structure) {
                this.tables = {};
                this.activeKey = null;
                for (const table of data.tables)
                    this.tables[table.name] = new Table(table, $structure, structure);
                for (const table of data.tables) {
                    for (const primary of table.keys.primaries)
                        this.SetPrimaryKey(primary.name, this.tables[table.name], primary.fields);
                    for (const foreigner of table.keys.foreigners)
                        this.SetForeignKey(foreigner.name, this.tables[table.name], foreigner.fields, foreigner.relationship_from, { table: this.tables[foreigner.references_table], fields: foreigner.references_fields, relationship: foreigner.relationship_to });
                }
            }
            SetPrimaryKey(name, table, fields) {
                let names = [];
                for (const field of fields)
                    names.push(table.fields[field]);
                new Primary(name, table, names, this);
            }
            SetForeignKey(name, table, fields, relationship, references) {
                let names = [];
                let references_names = [];
                for (const field of fields)
                    names.push(table.fields[field]);
                for (const field of references.fields)
                    references_names.push(references.table.fields[field]);
                new Foreign(name, table, names, relationship, { table: references.table, fields: references_names, relationship: references.relationship }, this);
            }
            SetActiveKey(key) {
                this.activeKey = key;
            }
            UnsetActiveKey() {
                this.activeKey = null;
            }
            GetActiveKey() {
                return this.activeKey;
            }
        }
        class Table {
            fields;
            $table;
            $drag;
            $header;
            $title;
            $name;
            $description;
            $menu;
            $rows;
            $keys;
            constructor(data, $structure, structure) {
                this.fields = {};
                this.Render(data, $structure, structure);
                for (const field of data['fields'])
                    this.fields[field.name] = new Field(field, this.$rows);
            }
            Render(data, $structure, structure) {
                this.$table = document.createElement('div');
                this.$table.className = 'table';
                this.$drag = document.createElement('div');
                this.$drag.className = 'drag';
                this.$header = document.createElement('div');
                this.$header.className = 'header';
                this.$title = document.createElement('div');
                this.$title.className = 'title';
                this.$name = document.createElement('div');
                this.$name.className = 'name';
                this.$description = document.createElement('div');
                this.$description.className = 'description';
                this.$menu = document.createElement('div');
                this.$menu.className = 'menu';
                this.$rows = document.createElement('div');
                this.$rows.className = 'rows';
                this.$keys = document.createElement('div');
                this.$keys.className = 'keys';
                this.$name.innerText = data.name;
                this.$description.innerText = data.description;
                this.$menu.innerText = '▼';
                this.$table.append(this.$drag, this.$header, this.$rows, this.$keys);
                this.$header.append(this.$title, this.$menu);
                this.$title.append(this.$name, this.$description);
                $structure.append(this.$table);
                DragAndDropInStructure(this.$drag, this.$table, data.name);
                this.$table.addEventListener('mouseover', () => structure.HoverElement(this.$table));
                let left, top;
                let position = localStorage.getItem(`structure_table_${data.name}`);
                if (position) {
                    [left, top] = position.split(',');
                    this.$table.style.left = `${left}px`;
                    this.$table.style.top = `${top}px`;
                }
            }
            AddKey(type, name, key) {
                let $wrap = document.createElement('div');
                let $type = document.createElement('div');
                $type.className = 'key_type';
                $type.innerText = type;
                let $name = document.createElement('div');
                $name.className = 'key_name';
                $name.innerText = name;
                this.$keys.append($wrap);
                $wrap.append($type, $name);
                $wrap.addEventListener('click', () => { key.Display(); });
                return $wrap;
            }
        }
        class Field {
            $wrap;
            $type;
            $name;
            $description;
            $key;
            static ER_RELATIONSHIP = {
                1: 'one',
                2: 'many',
                3: 'only_one',
                4: 'zero_or_one',
                5: 'one_or_many',
                6: 'zero_or_many'
            };
            constructor(data, $rows) {
                this.Render(data, $rows);
            }
            Render(data, $rows) {
                this.$wrap = document.createElement('div');
                this.$type = document.createElement('span');
                this.$type.className = 'type';
                this.$name = document.createElement('div');
                this.$name.className = 'name';
                this.$description = document.createElement('div');
                this.$description.className = 'description';
                this.$key = document.createElement('div');
                this.$key.className = 'key';
                this.$type.innerText = data.type;
                this.$name.innerText = data.name;
                this.$description.innerText = data.description;
                this.$wrap.append(this.$type, this.$name, this.$description, this.$key);
                $rows.append(this.$wrap);
            }
            SetPrimaryKey() {
                this.$key.innerText = 'Pr';
                this.$wrap.classList.add('primary');
            }
            UnsetPrimaryKey() {
                this.$key.innerText = '';
                this.$wrap.classList.remove('primary');
            }
            SetForeignKey(relationship) {
                this.$key.innerText = 'Fr';
                this.$wrap.classList.add('foreign', Field.ER_RELATIONSHIP[relationship]);
            }
            UnsetForeignKey(relationship) {
                this.$key.innerText = '';
                this.$wrap.classList.remove('foreign', Field.ER_RELATIONSHIP[relationship]);
            }
            SetReferencesKey(relationship) {
                this.$key.innerText = '*';
                this.$wrap.classList.add('key', 'references', Field.ER_RELATIONSHIP[relationship]);
            }
            UnsetReferencesKey(relationship) {
                this.$key.innerText = '';
                this.$wrap.classList.remove('key', 'references', Field.ER_RELATIONSHIP[relationship]);
            }
        }
        class Key {
            name;
            db;
            table;
            fields;
            display;
            $key;
            constructor(name, table, fields, db) {
                this.db = db;
                this.table = table;
                this.name = name;
                this.fields = fields;
                this.display = false;
            }
            Display() {
                if (this.display) {
                    this.Hide();
                    this.db.UnsetActiveKey();
                    return;
                }
                this.db.GetActiveKey()?.Display();
                this.Show();
                this.db.SetActiveKey(this);
            }
            Show() { }
            Hide() { }
        }
        class Primary extends Key {
            constructor(name, table, fields, db) {
                super(name, table, fields, db);
                this.$key = this.table.AddKey('primary', this.name, this);
            }
            Show() {
                this.display = true;
                this.$key.classList.add('active');
                for (const i in this.fields)
                    this.fields[i].SetPrimaryKey();
            }
            Hide() {
                this.display = false;
                this.$key.classList.remove('active');
                for (const i in this.fields)
                    this.fields[i].UnsetPrimaryKey();
            }
        }
        class Foreign extends Key {
            relationship;
            references;
            constructor(name, table, fields, relationship, references, db) {
                super(name, table, fields, db);
                this.relationship = relationship;
                this.references = references;
                this.$key = this.table.AddKey('foreign', this.name, this);
            }
            Show() {
                this.display = true;
                this.$key.classList.add('active');
                for (const i in this.fields)
                    this.fields[i].SetForeignKey(this.relationship);
                for (const i in this.references.fields)
                    this.references.fields[i].SetReferencesKey(this.references.relationship);
            }
            Hide() {
                this.display = false;
                this.$key.classList.remove('active');
                for (const i in this.fields)
                    this.fields[i].UnsetForeignKey(this.relationship);
                for (const i in this.references.fields)
                    this.references.fields[i].UnsetReferencesKey(this.references.relationship);
            }
        }
        function DragAndDropInStructure($drag, $elem, name) {
            $drag.onpointerdown = event => {
                $drag.setPointerCapture(event.pointerId);
                let startClientX = event.clientX;
                let startClientY = event.clientY;
                let startLeft = $elem.offsetLeft;
                let startTop = $elem.offsetTop;
                let left = null;
                let top = null;
                $drag.onpointermove = event => {
                    let alphaX = startClientX - event.clientX;
                    let alphaY = startClientY - event.clientY;
                    left = startLeft - alphaX;
                    if (left < 0)
                        left = 0;
                    top = startTop - alphaY;
                    if (top < 0)
                        top = 0;
                    $elem.style.left = `${left}px`;
                    $elem.style.top = `${top}px`;
                };
                $drag.onpointerup = () => {
                    $drag.onpointermove = null;
                    $drag.onpointerup = null;
                    localStorage.setItem(`structure_table_${name}`, [left, top].join(','));
                };
            };
        }
    })(General = Admin.General || (Admin.General = {}));
})(Admin || (Admin = {}));
//# sourceMappingURL=general.js.map