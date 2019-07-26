include Book;

module Styles = {
  open Css;

  let container = style([padding(px(100)), color(black)]);
  let form = [20 |> px |> paddingLeft, flexBox |> display] |> style;

  let item = [10 |> px |> marginLeft] |> style;

  let button =
    [
      10 |> px |> marginLeft,
      `pointer |> cursor,
      "fff" |> hex |> color,
      "007bff" |> hex |> backgroundColor,
      "007bff" |> hex |> borderColor,
      0.75 |> rem |> borderRadius,
    ]
    |> style;
};

module UpdateBookForm = {
  [@react.component]
  let make =
      (~editingBook, ~setTitle, ~setPreviewImage, ~setTags, ~updateBook) => {
    switch (editingBook) {
    | Some(book) =>
      <div className=Styles.form>
        <div>
          <input
            value={book.title}
            type_="text"
            placeholder="Title"
            onChange={e => setTitle(e->ReactEvent.Form.target##value)}
          />
        </div>
        <div className=Styles.item>
          <input
            value={book.previewImage}
            type_="text"
            placeholder="Image URL"
            onChange={e => setPreviewImage(e->ReactEvent.Form.target##value)}
          />
        </div>
        <div className=Styles.item>
          <input
            value={book.tags |> Array.of_list |> Js.Array.joinWith(", ")}
            type_="text"
            placeholder="Tags"
            onChange={e =>
              setTags(
                e->ReactEvent.Form.target##value
                |> Js.String.split(",")
                |> Array.to_list
                |> List.map(Js.String.trim),
              )
            }
          />
        </div>
        <button
          className=Styles.button
          onClick={_ =>
            updateBook({
              id: book.id,
              title: book.title,
              previewImage: book.previewImage,
              tags: book.tags,
            })
          }>
          {ReasonReact.string("Update book")}
        </button>
      </div>
    | None => <div />
    };
  };
};

module AddNewBookForm = {
  [@react.component]
  let make = (~books, ~addBook) => {
    let (title, setTitle) = React.useState(() => "");
    let (tags, setTags) = React.useState(() => "");
    let (previewImage, setPreviewImage) = React.useState(() => "");

    <div className=Styles.form>
      <div>
        <input
          value=title
          type_="text"
          placeholder="Title"
          onChange={e => setTitle(e->ReactEvent.Form.target##value)}
        />
      </div>
      <div className=Styles.item>
        <input
          value=previewImage
          type_="text"
          placeholder="Image URL"
          onChange={e => setPreviewImage(e->ReactEvent.Form.target##value)}
        />
      </div>
      <div className=Styles.item>
        <input
          value=tags
          type_="text"
          placeholder="Tags"
          onChange={e => setTags(e->ReactEvent.Form.target##value)}
        />
      </div>
      <button
        className=Styles.button
        onClick={_ =>
          addBook({
            id: Array.length(books) + 1,
            title,
            previewImage,
            tags:
              Js.String.split(",", tags)
              |> Array.to_list
              |> List.map(Js.String.trim),
          })
        }>
        {ReasonReact.string("Add new book")}
      </button>
    </div>;
  };
};

let book1 = {
  id: 0,
  title: "Exploring ReasonML and functional programming",
  tags: ["frontend", "ocaml"],
  previewImage: "http://bit.ly/2XMWrE7",
};
let book2 = {
  id: 1,
  title: "Learn Web Development with Rails",
  tags: ["backend", "ruby", "rails"],
  previewImage: "http://bit.ly/2y1hmEl",
};
let book3 = {
  id: 2,
  title: "The Rust Programming Language",
  tags: ["backend", "ownership"],
  previewImage: "http://bit.ly/2LozvnU",
};
let initialBooks = [|book1, book2, book3|];

let initEditingBook = None;

type action =
  | SetBook(book)
  | SetTitle(string)
  | SetPreviewImage(string)
  | SetTags(list(string))
  | None;

type state = {editingBook: option(book)};

let convertOption = book =>
  switch (book) {
  | Some(book) => string_of_int(book.id)
  | None => ""
  };

[@react.component]
let make = () => {
  let (books, setBooks) = React.useState(() => initialBooks);

  let (editingBook, dispatch) =
    React.useReducer(
      (editingBook, action) =>
        switch (editingBook) {
        | Some(book) =>
          switch (action) {
          | SetTitle(title) => Some({...book, title})
          | SetPreviewImage(previewImage) => Some({...book, previewImage})
          | SetTags(tags) => Some({...book, tags})
          | _ => Some(book)
          }
        | None =>
          switch (action) {
          | SetBook(book) => Some(book)
          | _ => editingBook
          }
        },
      initEditingBook,
    );

  <div className=Styles.container>
    {books
     |> Array.map(book =>
          <Book
            key={string_of_int(book.id)}
            bookItem=book
            setEditingBook={bookItem => dispatch(SetBook(bookItem))}
          />
        )
     |> ReasonReact.array}
    <AddNewBookForm
      books
      addBook={addedBook =>
        setBooks(_ => Array.append([|addedBook|], books))
      }
    />
    <br />
    <UpdateBookForm
      editingBook
      setTitle={title => dispatch(SetTitle(title))}
      setPreviewImage={previewImage =>
        dispatch(SetPreviewImage(previewImage))
      }
      setTags={tags => dispatch(SetTags(tags))}
      updateBook={editingBook =>
        setBooks(_ =>
          Array.map(
            book => book.id == editingBook.id ? editingBook : book,
            books,
          )
        )
      }
    />
  </div>;
};
