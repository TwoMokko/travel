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
    })(General = Admin.General || (Admin.General = {}));
})(Admin || (Admin = {}));
//# sourceMappingURL=general.js.map