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
        this.$select_categories.attr('autocomplete', 'off');
        this.$select_tours.attr('autocomplete', 'off');
        this.$select_categories.on('change', this.RestructureTours.bind(this));
        this.$select_tours.on('change', this.RestructureBtn.bind(this));
        this.RestructureCategory();
    }
    RestructureCategory() {
        for (let i in this.data) {
            if (IsEmpty(this.data[i].tours))
                continue;
            this.$select_categories.append($('<option/>', { value: i }).text(this.data[i].name));
        }
        this.$select_categories.trigger('change');
    }
    RestructureTours() {
        let category = Number(this.$select_categories.val());
        this.$select_tours.empty();
        if (!category)
            return;
        for (let i in this.data[category].tours) {
            this.$select_tours.append($('<option/>', { value: i }).text(this.data[category].tours[i].name));
        }
        this.$select_tours.trigger('change');
    }
    RestructureBtn() {
        let category = this.$select_categories.val().toString();
        let tour = this.$select_tours.val();
        this.$btn_see_tour.attr('href', this.data[category].tours[tour].href);
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
function ToDrive(tour_id) {
    let $form = $('<form/>', { class: '', action: '/feedback' });
    let $name = $('<input/>', { name: 'name', class: '', type: 'text', placeholder: 'Имя*', minlength: '3', maxlength: '50' });
    let $call = $('<input/>', { name: 'contact', class: '', type: 'text', placeholder: 'Способ связи*', minlength: '3', maxlength: '50' });
    let $send = $('<a/>', { class: 'button', text: 'Отправить' });
    $send.on('click', () => {
        if (Validation.Form($form))
            Base.Common.Query.SendForm($form, Success);
    });
    $form.append($('<input/>', { name: 'tour_id', type: 'hidden', value: tour_id }), $name, $call, $send);
    let wind = Common.Window.Create('Оставьте заявку', $form);
    function Success() {
        wind.Close();
        Common.Window.ShowMessage('Спасибо, ваша заяка принята');
    }
}
/**
 * Вывод формы обратной связи через кнопку "поехать" в "tours"
 * @constructor
 */
function LeaveReview(avatars) {
    console.log(avatars);
    let $form = $('<form/>', { class: '', action: '/review/add' });
    let $name = $('<input/>', { name: 'name', class: '', type: 'text', placeholder: 'Имя*', minlength: '3', maxlength: '50' });
    let $text_container = $('<div/>', { class: '' });
    let $text = $('<textarea/>', { name: 'text', class: '', type: 'text', placeholder: 'Напишите отзыв*', rows: '5', maxlength: '255' });
    let $avatar_container = $('<span/>', { class: 'avatar_container' });
    let $send = $('<a/>', { class: 'button', text: 'Отправить' });
    $send.on('click', () => {
        if (Validation.Form($form))
            Base.Common.Query.SendForm($form, Success);
    });
    for (let i in avatars) {
        let $label = $('<label/>', { class: '' });
        let $ava = $('<div/>', { class: 'ava' });
        let $radio = $('<input/>', { type: 'radio', class: 'hide', value: i, name: 'avatar' });
        $ava.css('background-image', `url(${avatars[i]})`).on('click', () => {
            $avatar_container.find('.active').removeClass('active');
            $ava.hasClass('active') ? $ava.removeClass('active') : $ava.addClass('active');
        });
        $avatar_container.append($label.append($ava, $radio));
    }
    $form.append($name, $text_container.append($text), $avatar_container, $send);
    let wind = Common.Window.Create('Оставьте отзыв', $form);
    function Success() {
        wind.Close();
        Common.Window.ShowMessage('Спасибо за отзыв');
    }
}
function ShowVideo() {
    console.log('123');
    let $iframe = $('<iframe/>', { class: 'show_video', src: 'https://www.youtube.com/embed/XDziNYkyFww', allowfullscreen: '', frameborder: 0 });
    let $video = $('<video/>', { class: 'show_video', controls: 'controls' });
    let $source = $('<source/>', { src: 'https://youtu.be/XDziNYkyFww' });
    // $video.append($source);
    Common.Window.Create('Смотреть видео', $iframe);
    $iframe.parent().removeClass('container');
}
class Validation {
    static Form($form) {
        let $check = true;
        let $elements = $form.find('input[type="text"], textarea');
        $elements.each((i, element) => {
            let value = '';
            switch ($(element).prop('nodeName')) {
                case 'INPUT':
                    value = $(element).val().toString();
                    break;
                case 'TEXTAREA':
                    value = $(element).text();
                    break;
            }
            if (!Validation.Element($(element), value))
                $check = false;
        });
        return $check;
    }
    static Element($element, value) {
        let errors = [];
        let minlength = $element.attr('minlength');
        if ((minlength != undefined) && (value.trim().length < Number(minlength)))
            errors.push(`Не менее ${minlength} символов`);
        let maxlength = Number($element.attr('maxlength'));
        if ((maxlength != undefined) && (value.trim().length > Number(maxlength)))
            errors.push(`Не более ${maxlength} символов`);
        if (errors.length) {
            Validation.ShowErrors($element, errors);
            return false;
        }
        Validation.HideErrors($element);
        return true;
    }
    static ShowErrors($element, errors) {
        // $element.next('.validation_error').remove();
        // let $errors = $('<span/>', {class: 'validation_error', title: errors.join(`\n`)});
        // $element.after($errors);
        $element.addClass('error');
    }
    static HideErrors($element) {
        // $element.next('.validation_error').remove();
        $element.removeClass('error');
    }
}
/**
 * Вывод окна после отправки данных пользователем
 * @constructor
 */
function AfterSend() {
    Common.Window.ShowMessage('Спасибо, ваша заяка принята');
}
function GetReview(path, id) {
    Base.Common.Query.SendData(path, { id: id }, ShowReview);
}
function ShowReview(data) {
    let $review = $('<div/>', { class: 'review_window' });
    $review.append($('<div/>', { class: 'review_person' }).append($('<div/>').css('background-image', `url(${data['image']})`), $('<div/>').text(data['name'])), $('<div/>', { class: 'review_text' }).text(data['text']));
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
        $('main').append(this.$gallery.append($space, this.$photo, $container_btn.append($close, (this.images.length > 1) ? $arrow_left : $(), (this.images.length > 1) ? $arrow_right : $())));
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
        let $div6 = $('<div/>');
        let $page1 = $('<a/>', { class: 'page1', text: 'Главная', href: '/' });
        let $page2 = $('<a/>', { class: 'page2', text: 'Путешествия', href: '/tours' });
        let $page3 = $('<a/>', { class: 'page3', text: 'О нас', href: '/about' });
        let $page4 = $('<a/>', { class: 'page4', text: 'Дневник путешествий', href: '/stories' });
        let $page5 = $('<a/>', { class: 'page5', text: 'Отзывы', href: '/review' });
        let $page6 = $('<a/>', { class: 'page5', text: 'Фотоальбомы', href: '/photo' });
        /* Building DOM */
        $('body').append(this.$container.append($space, 
        // $content.append(
        $close, $pages.append($div1.append($page1), $div2.append($page2), $div3.append($page3), $div4.append($page4), $div5.append($page5), $div6.append($page6))
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
class Carousel {
    /* Variables */
    active;
    count;
    /* Elements */
    $container;
    $wrap;
    $scroll;
    $items;
    $manage;
    $array_left;
    $array_right;
    constructor(container) {
        /*  */
        this.$container = $(container);
        this.count = 1;
        this.$items = [];
        this.active = 0;
        this.$container.children().each((index, element) => {
            let $element = $(element);
            this.$items.push($element);
            $element.detach();
        });
        /* Set elements */
        this.$wrap = $('<div/>', { class: 'wrap' });
        this.$scroll = $('<div/>', { class: 'scroll' });
        this.$manage = $('<div/>', { class: 'manage' });
        this.$array_left = $('<div/>');
        this.$array_right = $('<div/>');
        /* Building DOM */
        this.$container.append(this.$manage.append(this.$array_left, this.$array_right), this.$wrap.append(this.$scroll));
        /* Events */
        this.$array_left.on('click', () => {
            this.GetActive('left');
            this.ShowItems();
        });
        this.$array_right.on('click', () => {
            this.GetActive('right');
            this.ShowItems();
        });
        this.$container.addClass('carousel');
        $(window).on('resize', this.Restructure.bind(this));
        this.Restructure();
    }
    Restructure() {
        let gtc = this.$scroll.css('grid-template-columns');
        this.count = (gtc !== 'none') ? this.$scroll.css('grid-template-columns').split(' ').length : 1;
        if (this.count >= this.$items.length) {
            this.$array_left.addClass('hide');
            this.$array_right.addClass('hide');
        }
        else {
            this.$array_left.removeClass('hide');
            this.$array_right.removeClass('hide');
        }
        this.ShowItems();
    }
    ShowItems() {
        this.$scroll.children().each((index, element) => {
            let $element = $(element);
            $element.detach();
        });
        for (let i = 0, a = this.active; i < this.count && i <= (this.$items.length - 1); i++) {
            this.ShowItem(a);
            a = this.GetNext(a);
        }
    }
    ShowItem(a) {
        this.$scroll.append(this.$items[a]);
    }
    GetNext(a) {
        if (a >= (this.$items.length - 1))
            return 0;
        else
            return ++a;
    }
    GetActive(side) {
        switch (side) {
            case ('left'):
                if (this.active == 0)
                    this.active = (this.$items.length - 1);
                else
                    this.active--;
                break;
            case ('right'):
                if (this.active == (this.$items.length - 1))
                    this.active = 0;
                else
                    this.active++;
                break;
        }
    }
}
//# sourceMappingURL=common.js.map