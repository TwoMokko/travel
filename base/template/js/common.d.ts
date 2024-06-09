/// <reference types="jquery" />
/// <reference types="jquery" />
declare namespace Base {
    namespace Common {
        type DebugData = {
            network: DebugNetwork;
            post: DebugVar[];
            get: DebugVar[];
            files: DebugVar[];
            variables: DebugVar[];
            queries: DebugQuery[];
            controllers: DebugController[];
            models: DebugModule[];
            timestamps: DebugTimestamp[];
            user: DebugUser;
        };
        type DebugNetwork = {
            area: string;
            part: string;
            point: string;
            type: string;
            href: string;
            ip: string;
        };
        type DebugVar = {
            title: string;
            var: DebugVariable;
        };
        type DebugQuery = string;
        type DebugController = {
            name: string;
            file: string;
        };
        type DebugModule = {
            name: string;
            file: string;
        };
        type DebugTimestamp = {
            name: string;
            time: number;
            start: number;
            stop: number;
        };
        type DebugUser = {
            name: string;
        };
        type DebugVariable = DebugInteger | DebugDouble | DebugString | DebugNull | DebugArray | DebugObject;
        type DebugInteger = {
            type: 'integer';
            value: number;
        };
        type DebugDouble = {
            type: 'double';
            value: number;
        };
        type DebugString = {
            type: 'string';
            value: string;
        };
        type DebugNull = {
            type: 'null';
            value: null;
        };
        type DebugArray = {
            type: 'array';
            value: DebugArrayContent[];
        };
        type DebugObject = {
            type: 'object';
            value: DebugObjectContent;
        };
        type DebugArrayContent = {
            key: DebugArrayKey;
            value: DebugVariable;
        };
        type DebugArrayKey = {
            type: 'integer';
            value: number;
        } | {
            type: 'double';
            value: number;
        } | {
            type: 'string';
            value: string;
        };
        type DebugObjectContent = {
            namespace: string;
            name: string;
            modifiers: DebugObjectModifier[];
            constants: DebugObjectConstant[];
            properties: DebugObjectProperty[];
            methods: DebugObjectMethod[];
        };
        type DebugObjectConstant = {
            modifiers: DebugObjectConstantsModifier[];
            name: string;
            value: DebugVariable;
        };
        type DebugObjectProperty = {
            modifiers: DebugObjectPropertiesModifier[];
            name: string;
            value: DebugVariable;
        };
        type DebugObjectMethod = {
            modifiers: DebugObjectMethodsModifier[];
            name: string;
        };
        type DebugObjectModifier = 'abstract' | 'implicit' | 'explicit' | 'final' | 'readonly';
        type DebugObjectConstantsModifier = 'public' | 'protected' | 'private' | 'final';
        type DebugObjectPropertiesModifier = 'public' | 'protected' | 'private' | 'static' | 'readonly';
        type DebugObjectMethodsModifier = 'public' | 'protected' | 'private' | 'final' | 'static' | 'abstract';
        export class Debugger {
            private static iter;
            private static open;
            private static data;
            private static dataActive;
            private static spaces;
            private static spaceActive;
            private static record;
            private static track;
            private static $receiver;
            private static $container;
            private static $manager;
            private static $toggle;
            private static $setting;
            private static $s_record;
            private static $s_track;
            private static $s_clear;
            private static $work;
            private static $drag;
            private static $spaces;
            private static $panel;
            private static $btns;
            static Initialization(): void;
            static Append(data: DebugData): void;
            static Load(iter: number): void;
            private static ToggleSpase;
            private static ToggleRecord;
            private static ToggleTrack;
            private static OpenSpace;
            private static ClearAll;
        }
        export {};
    }
}
declare function getCookie(name: string): string | null;
declare function setCookie(name: any, value: any, options?: {}): void;
declare function deleteCookie(name: string): void;
declare function getContent(route?: string): void;
declare namespace Base {
    namespace Common {
        class History {
            static Initialization(): void;
            static Replace(address: any, xhr: any): void;
        }
    }
}
declare namespace Base {
    namespace Common {
        class Layout {
            static Initialization(): void;
        }
    }
}
declare namespace Base {
    namespace Common {
        type TypeNotice = 'ok' | 'error' | 'info' | 'common';
        export class Notice {
            private static iter;
            private static notices;
            static $notices: any;
            static Create(type: TypeNotice, html: string): Instance;
            static Ok(html: string | JQuery): Instance;
            static Info(html: string | JQuery): Instance;
            static Error(html: string | JQuery): Instance;
            private static New;
            static Delete(id: number): void;
        }
        class Instance {
            id: number;
            $instance: JQuery;
            constructor(id: number, type: TypeNotice, html: string | JQuery);
            Close(): void;
            private Remove;
        }
        export {};
    }
}
declare namespace Base {
    namespace Common {
        class GlobalParams {
            private static param;
            static Set(name: string, value: any): void;
            static Get(name: any): any;
        }
    }
}
declare namespace Base {
    namespace Common {
        type TypeRequestParams = {
            method?: 'get' | 'post';
            request?: string;
            processData?: boolean;
            contentType?: string | false;
        };
        export class Query {
            static SendData(address: string, data: Object, handler?: Function, params?: TypeRequestParams): void;
            static Send(address: string, handler?: Function, params?: TypeRequestParams): void;
            static SendForm(form: JQuery, handler?: Function): void;
            static SubmitForm(th: any, handler?: Function): void;
            static SubmitFormEvent(e: any, handler?: Function): void;
            private static Response;
            private static Execute;
            private static ExecuteHistory;
            private static ExecuteSection;
            private static ExecuteNotice;
            private static ExecuteHandler;
        }
        export {};
    }
}
declare namespace Base {
    namespace Common {
        class Section {
            private $_elem;
            constructor($_elem: JQuery);
            Fill(...contents: any[]): void;
            Push(...contents: any[]): void;
        }
    }
}
declare namespace Base {
    namespace Skins {
        type TypeColumn = {
            alias: string;
            name: string;
            type: string;
        };
        type TypeColumns = {
            [key: string]: TypeColumn;
        };
        type TypeValue = {
            [key: string]: any;
        };
        type TypeValues = TypeValue[];
        export class Table {
            number: number;
            name: string;
            columns: TypeColumns;
            $container: JQuery;
            $table: JQuery;
            $thead: JQuery;
            $tr_head: JQuery;
            $tbody: JQuery;
            $add: JQuery;
            constructor(selector: string, name: string, columns: TypeColumns, values?: TypeValues);
            private AddColumn;
            private GetInput;
            private GetTextarea;
        }
        type TypePhotos = {
            [key: string]: {
                id: number;
                image: string;
            };
        };
        export class UploaderPhoto {
            $wrap: JQuery;
            $input: JQuery;
            $space: JQuery;
            $container: JQuery;
            path_load: string;
            path_del: string;
            path_view: string;
            constructor(selector: string, text: string, path_load: string, path_del: string, path_view: string, photos: TypePhotos);
            private LoadFiles;
            private ShowFiles;
        }
        export {};
    }
}
