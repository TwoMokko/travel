/// <reference types="jquery" />
/// <reference types="jquery" />
/**
 * Навигация по турам на странице "tours"
 * @param selector
 * @param top_absolute
 * @param top_fixed
 * @constructor
 */
declare function NavigationTour(selector: string, top_absolute: number, top_fixed: number): void;
/**
 * Появление кнопки для рокрутки страницы наверх
 * @param selector
 * @constructor
 */
declare function ScrollTop(selector: string): void;
declare type TypeTour = {
    id: number;
    name: string;
    href: string;
};
declare type TypeCategory = {
    id: number;
    name: string;
    tours: TypeTour[];
};
/**
 * Работа с селектами на главной странице
 */
declare class SelectTour {
    data: TypeCategory[];
    $select_categories: JQuery;
    $select_tours: JQuery;
    $btn_see_tour: JQuery;
    constructor(data: TypeCategory[]);
    private RestructureCategory;
    private RestructureTours;
    private RestructureBtn;
}
declare function Switcher(selector_menu: any, selector_list: any): void;
/**
 * Вывод формы обратной связи через кнопку "поехать" в "tours"
 * @constructor
 */
declare function ToDrive(): void;
/**
 * Вывод окна после отправки данных пользователем
 * @constructor
 */
declare function AfterSend(): void;
declare function SeeReview(th: any): void;
declare namespace Common {
    /**
     * Менеджер работы с окнами
     */
    export class Window {
        private static windows;
        private static iter;
        static $windows: any;
        static ShowMessage(text: string): Instance;
        static Create(title: string | null, content: JQuery | string): Instance;
        static Remove(id: number): void;
    }
    /**
     * Работа с окнами
     */
    class Instance {
        private readonly id;
        private readonly $instance;
        constructor(id: number, title: string | null, content: JQuery | string);
        Close(): void;
        private Remove;
    }
    export {};
}
/**
 * Работа с просмотрщиком фотографий
 */
declare class Gallery {
    images: string[];
    active: number;
    $th: JQuery;
    $gallery: JQuery;
    $photo: JQuery;
    imageWidth: number;
    imageHeight: number;
    percent: number;
    constructor(th: HTMLElement);
    /**
     *
     * @param e
     * @constructor
     * @private
     */
    private static OnResize;
    /**
     *
     * @param e
     * @constructor
     * @private
     */
    private OnKeyDown;
    /**
     *
     * @constructor
     * @private
     */
    private SearchImages;
    /**
     * Показать фотографию
     * @constructor
     * @private
     */
    private ShowImage;
    /**
     *
     * @constructor
     * @private
     */
    private GetSize;
    /**
     *
     * @param self
     * @constructor
     * @private
     */
    private NewSize;
    /**
     *
     * @param gallerySize
     * @constructor
     * @private
     */
    private GetNewSize;
    /**
     *
     * @param size
     * @constructor
     * @private
     */
    private Resize;
    /**
     * Закрыть галерею и очистить данные
     * @constructor
     */
    Close(): void;
    /**
     * Листать фотографию влево
     * @constructor
     */
    Left(): void;
    /**
     * Листать фотографию вправо
     * @constructor
     */
    Right(): void;
}
declare class Menu {
    $container: JQuery;
    constructor(th: HTMLElement);
    Close(): void;
}
