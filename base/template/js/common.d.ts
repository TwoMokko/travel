/// <reference types="jquery" />
/// <reference types="jquery" />
declare namespace Base {
    namespace Common {
        export class GlobalParams {
            private static param;
            static Set(name: string, value: any): void;
            static Get(name: any): any;
        }
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
        }
        export class Section {
            private $_elem;
            constructor($_elem: JQuery);
            Fill(...contents: any[]): void;
            Push(...contents: any[]): void;
        }
        export class Layout {
            static Initialization(): void;
        }
        export {};
    }
}
