include Book;

module Styles = {
  open Css;

  let container = style([padding(px(100)), color(black)]);
  let form = [
    20 |> px |> paddingLeft,
    flexBox |> display
  ] |> style;

  let item = [
    10 |> px |> marginLeft
  ] |> style;

  let button = [
    10 |> px |> marginLeft,
    `pointer |> cursor,
    "fff" |> hex |> color,
    "007bff" |> hex |> backgroundColor,
    "007bff" |> hex |> borderColor,
    0.75 |> rem |> borderRadius
  ] |> style;
};

module AddNewBookForm = {
  [@react.component]
  let make = (~addBook) => {
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
        onClick={
          _ => addBook({
            title: title,
            previewImage: previewImage,
            tags: Js.String.split(",", tags) |> Array.to_list |> List.map(Js.String.trim)
          })
        }
      >
        {ReasonReact.string("Add new book")}
      </button>
    </div>;
  }
}

let book1 = {
  title: "Exploring ReasonML and functional programming",
  tags: ["frontend", "ocaml"],
  previewImage: "http://bit.ly/2XMWrE7",
};
let book2 = {
  title: "Learn Web Development with Rails",
  tags: ["backend", "ruby", "rails"],
  previewImage: "http://bit.ly/2y1hmEl",
};
let book3 = {
  title: "The Rust Programming Language",
  tags: ["backend", "ownership"],
  previewImage: "http://bit.ly/2LozvnU",
};
let initialBooks = [book1, book2, book3];

[@react.component]
let make = () => {
  let (books, setBooks) = React.useState(() => initialBooks);

  <div className=Styles.container>
    {books
     |> List.map(book =>
          <Book
            key={book.title}
            title={book.title}
            tags={book.tags}
            previewImage={book.previewImage}
          />
        )
     |> Array.of_list
     |> ReasonReact.array}
     <AddNewBookForm addBook={book => setBooks(books => [book, ...books])}/>
  </div>;
};
