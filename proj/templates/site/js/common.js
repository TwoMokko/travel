"use strict";
/**
 * Навигация по турам на странице "tours"
 * @param selector
 * @param top_absolute
 * @param top_fixed
 * @constructor
 */
function NavigationTour(selector, top_absolute, top_fixed) {
    let $document = $(document);
    let $selector = $(selector);
    let $parent = $selector.parent();
    $document.on('scroll', Redraw);
    function Redraw() {
        let _top = $parent.offset().top;
        let _scroll = $document.scrollTop();
        if (_top + (top_absolute - top_fixed) <= _scroll)
            $selector.css({ position: 'fixed', top: `${top_fixed}px` });
        else
            $selector.css({ position: 'absolute', top: `${top_absolute}px` });
    }
    Redraw();
}
/**
 * Появление кнопки для рокрутки страницы наверх
 * @param selector
 * @constructor
 */
function ScrollTop(selector) {
    /*Elements*/
    let $document = $(document);
    let $elem = $(selector);
    let $button = $('<span/>', { class: 'arrow_top' });
    /*Building DOM*/
    $elem.append($button);
    /*Events*/
    $document.on('scroll', Redraw);
    $button.on('click', () => { $document.scrollTop(0); });
    function Redraw() {
        let _top = $elem.offset().top;
        let _scroll = $document.scrollTop();
        (_top < _scroll) ? $button.addClass('show') : $button.removeClass('show');
    }
    Redraw();
}
/**
 * Работа с селектами на главной странице
 */
class SelectTour {
    data;
    $select_categories;
    $select_tours;
    $btn_see_tour;
    constructor(data) {
        this.data = data;
        this.$select_categories = $('#categories');
        this.$select_tours = $('#tours');
        this.$btn_see_tour = $('#see_tour');
        this.$select_categories.on('change', this.RestructureTours.bind(this));
        this.$select_tours.on('change', this.RestructureBtn.bind(this));
        this.RestructureCategory();
    }
    RestructureCategory() {
        for (let i in this.data) {
            this.$select_categories.append($('<option/>', { value: i }).text(this.data[i].name));
        }
        this.$select_categories.trigger('change');
    }
    RestructureTours() {
        let category = Number(this.$select_categories.val());
        this.$select_tours.empty();
        for (let i in this.data[category].tours) {
            this.$select_tours.append($('<option/>', { value: this.data[category].tours[i].href }).text(this.data[category].tours[i].name));
        }
        this.$select_tours.trigger('change');
    }
    RestructureBtn() {
        this.$btn_see_tour.attr('href', this.$select_tours.val().toString());
    }
}
function Switcher(selector_menu, selector_list) {
    let $menu = $(selector_menu);
    let $list = $(selector_list);
    $menu.find('> *:first-child').addClass('active');
    $list.find('> *:not(:first-child)').addClass('hide');
    $menu.children().each((key, elem) => {
        let $elem = $(elem);
        $(elem).on('click', () => DoSwitch(key, $elem));
    });
    function DoSwitch(key, $elem) {
        $menu.children().removeClass('active');
        $elem.addClass('active');
        $list.children().addClass('hide');
        $list.find(`> *:nth-child(${key + 1})`).removeClass('hide');
    }
}
/**
 * Вывод формы обратной связи через кнопку "поехать" в "tours"
 * @constructor
 */
function ToDrive() {
    let $form = $('<form/>', { class: '' });
    let $name = $('<input/>', { class: '', type: 'text', placeholder: 'Имя*' });
    let $call = $('<input/>', { class: '', type: 'text', placeholder: 'Способ связи*' });
    let $send = $('<a/>', { class: 'button', text: 'Отправить' });
    $form.append($name, $call, $send);
    let wind = Common.Window.Create('Оставьте заявку', $form);
    $send.on('click', Success);
    function Success() {
        $send.closest('form').submit();
        wind.Close();
        Common.Window.ShowMessage('Спасибо, ваша заяка принята');
    }
}
/**
 * Вывод окна после отправки данных пользователем
 * @constructor
 */
function AfterSend() {
    Common.Window.ShowMessage('Спасибо, ваша заяка принята');
}
function SeeReview(th) {
    let $th = $(th);
    let name = $th.find('> .review_person > div:last-child').text();
    let text = $th.children('.review_text').text();
    let $review = $('<div/>', { class: 'review_window' });
    let $person = $('<div/>', { class: 'review_person' });
    let $photo = $('<div/>');
    let $name = $('<div/>').text(name);
    let $text = $('<div/>', { class: 'review_text' }).text(text);
    $review.append($person.append($photo, $name), $text);
    Common.Window.Create('✎', $review);
}
var Common;
(function (Common) {
    /**
     * Менеджер работы с окнами
     */
    class Window {
        static windows = {};
        static iter = 0;
        static $windows = null;
        static ShowMessage(text) {
            return Window.Create(null, text);
        }
        static Create(title = null, content) {
            if (!Window.$windows) {
                Window.$windows = $('<div/>', { class: 'windows' });
                $('main').append(Window.$windows);
            }
            let id = ++Window.iter;
            let wind = new Instance(id, title, content);
            Window.windows[id] = wind;
            return wind;
        }
        static Remove(id) {
            delete Window.windows[id];
        }
    }
    Common.Window = Window;
    /**
     * Работа с окнами
     */
    class Instance {
        id;
        $instance;
        constructor(id, title, content) {
            this.id = id;
            this.$instance = $('<div/>', { class: 'instance' });
            let $space = $('<div/>', { class: 'space' });
            let $window = $('<div/>', { class: 'window' });
            let $header = $('<div/>');
            let $title = $('<div/>', { class: 'title' });
            let $close = $('<div/>', { class: 'close' });
            let $container = $('<div/>');
            (title !== null) ? $header.addClass('head') : $header.addClass('head_null_title');
            (title !== null) ? $container.addClass('container') : $container.addClass('container_null_title');
            this.$instance.append($space, $window.append($header.append((title !== null) ? $title.append(title) : $(), $close), $container.append(content)));
            $space.on('click', this.Close.bind(this));
            $close.on('click', this.Close.bind(this));
            Window.$windows.append(this.$instance);
        }
        Close() {
            this.$instance.remove();
            this.Remove();
        }
        Remove() {
            Window.Remove(this.id);
        }
    }
})(Common || (Common = {}));
/**
 * Работа с просмотрщиком фотографий
 */
class Gallery {
    /* Variables */
    images;
    active;
    /* Elements */
    $th;
    $gallery;
    $photo;
    imageWidth;
    imageHeight;
    percent;
    constructor(th) {
        this.$th = $(th);
        this.percent = 0.8;
        if (!this.SearchImages())
            return;
        /* Set elements */
        this.$gallery = $('<div/>', { class: 'gallery' });
        this.$photo = $('<span>', { class: 'photo_gallery' });
        let $space = $('<div/>', { class: 'space' });
        let $container_btn = $('<div/>', { class: 'container_btn' });
        let $close = $('<span>', { class: 'close' });
        let $arrow_left = $('<span>', { class: 'arrow_left' });
        let $arrow_right = $('<span>', { class: 'arrow_right' });
        /* Building DOM */
        $('main').append(this.$gallery.append($space, this.$photo, $container_btn.append($close, $arrow_left, $arrow_right)));
        /* Events */
        $space.on('click', this.Close.bind(this));
        $close.on('click', this.Close.bind(this));
        $arrow_left.on('click', this.Left.bind(this));
        $arrow_right.on('click', this.Right.bind(this));
        $(window).on('resize', { self: this }, Gallery.OnResize);
        $(document).on('keydown.gallery', this.OnKeyDown.bind(this));
        this.ShowImage();
    }
    /**
     *
     * @param e
     * @constructor
     * @private
     */
    static OnResize(e) {
        let self = e.data.self;
        self.NewSize(self);
    }
    /**
     *
     * @param e
     * @constructor
     * @private
     */
    OnKeyDown(e) {
        switch (e.originalEvent.keyCode) {
            case 39:
                this.Right();
                break;
            case 32:
                this.Right();
                return false;
            case 37:
            case 8:
                this.Left();
                break;
            case 27:
                this.Close();
                break;
        }
        return true;
    }
    /**
     *
     * @constructor
     * @private
     */
    SearchImages() {
        this.images = [];
        let id = this.$th.data('id');
        let $images = $(`[data-id=${id}]`);
        this.active = 0;
        $images.each((key, element) => {
            let $element = $(element);
            this.images.push($element.data('url'));
            if ($element.is(this.$th))
                this.active = key;
        });
        return !!this.images.length;
    }
    /**
     * Показать фотографию
     * @constructor
     * @private
     */
    ShowImage() {
        this.$photo.css('background-image', `url(${this.images[this.active]})`);
        this.GetSize();
    }
    /**
     *
     * @constructor
     * @private
     */
    GetSize() {
        let img = new Image();
        img.src = this.images[this.active];
        img.onload = () => {
            this.imageWidth = img.width;
            this.imageHeight = img.height;
            this.NewSize(this);
        };
    }
    /**
     *
     * @param self
     * @constructor
     * @private
     */
    NewSize(self) {
        let gallerySize = [self.$gallery.width(), self.$gallery.height()];
        let newSize = self.GetNewSize(gallerySize);
        this.Resize(newSize);
        console.log('работает');
    }
    /**
     *
     * @param gallerySize
     * @constructor
     * @private
     */
    GetNewSize(gallerySize) {
        let resultWidth = this.imageWidth;
        let resultHeight = this.imageHeight;
        let a = this.imageWidth / this.imageHeight;
        if (this.imageWidth > (gallerySize[0] * this.percent) || this.imageHeight > (gallerySize[1] * this.percent)) {
            if (this.imageWidth / gallerySize[0] > this.imageHeight / gallerySize[1]) {
                resultWidth = gallerySize[0] * this.percent;
                resultHeight = resultWidth / a;
            }
            else {
                resultHeight = gallerySize[1] * this.percent;
                resultWidth = resultHeight * a;
            }
        }
        return [resultWidth, resultHeight];
    }
    /**
     *
     * @param size
     * @constructor
     * @private
     */
    Resize(size) {
        this.$photo.css({ width: `${size[0]}px`, height: `${size[1]}px` });
    }
    /**
     * Закрыть галерею и очистить данные
     * @constructor
     */
    Close() {
        this.$gallery.remove();
        $(window).off('resize', Gallery.OnResize);
        $(document).off('keydown.gallery');
    }
    /**
     * Листать фотографию влево
     * @constructor
     */
    Left() {
        this.active = (this.active) ? this.active - 1 : this.images.length - 1;
        this.ShowImage();
    }
    /**
     * Листать фотографию вправо
     * @constructor
     */
    Right() {
        this.active = (this.active !== this.images.length - 1) ? this.active + 1 : 0;
        this.ShowImage();
    }
}
class Menu {
    $container;
    constructor(th) {
        /* Set elements */
        this.$container = $('<div/>', { class: 'mini_menu' });
        let $space = $('<div/>', { class: 'space' });
        let $content = $('<div/>', { class: 'content_menu' });
        let $close = $('<div/>', { class: 'close_menu' });
        let $pages = $('<div/>', { class: 'pages_menu' });
        let $div1 = $('<div/>');
        let $div2 = $('<div/>');
        let $div3 = $('<div/>');
        let $div4 = $('<div/>');
        let $div5 = $('<div/>');
        let $page1 = $('<a/>', { class: 'page1', text: 'Главная', href: '/' });
        let $page2 = $('<a/>', { class: 'page2', text: 'Путешествия', href: '/tours' });
        let $page3 = $('<a/>', { class: 'page3', text: 'О нас', href: '/about' });
        let $page4 = $('<a/>', { class: 'page4', text: 'Наши приключения', href: '/adventures' });
        let $page5 = $('<a/>', { class: 'page5', text: 'Фотографии', href: '/photo' });
        /* Building DOM */
        $('body').append(this.$container.append($space, 
        // $content.append(
        $close, $pages.append($div1.append($page1), $div2.append($page2), $div3.append($page3), $div4.append($page4), $div5.append($page5))
        // )
        ));
        $space.on('click', this.Close.bind(this));
        $close.on('click', this.Close.bind(this));
        $('.open_menu').addClass('hide');
    }
    Close() {
        this.$container.remove();
        $('.open_menu').removeClass('hide');
    }
}
//# sourceMappingURL=common.js.map