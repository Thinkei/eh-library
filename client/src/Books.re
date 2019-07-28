include Book;
open Shipper;
open Ehd

module Styles = {
  open Css;

  let container = style([padding(px(100)), color(black)]);

  let bookList = [
    display(grid),
    gridColumnGap(px(24)),
    gridTemplateColumns([`repeat(`num(4), `fr(1.0))]),
  ] |> style

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

  let bookWrapper = [
    display(flexBox),
    borderBottom(px(1), solid, dimgrey),
    justifyContent(spaceBetween),
    alignItems(center),
  ] |> style;
};

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
let initialShippers = [
  {id: 0, name: "Shipper 1", info: "test 1"},
  {id: 1, name: "Shipper 2", info: "test 2"},
  {id: 2, name: "Shipper 3", info: "test 3"},
];

[@react.component]
let make = () => {
  let (books, setBooks) = React.useState(() => initialBooks);
  let (shippers, setShippers) = React.useState(() => initialShippers);
  let (editingShipperId, setEditingShipper) = React.useState(() => None);
  let (openEditModal, toggleEditModal) = React.useState(() => false);

  let updateShipper = ({id, name, info}) => {
    setShippers(_ =>
      List.map(
        shipper =>
          if (shipper.id === id) {
            {id, name, info};
          } else {
            shipper;
          },
        shippers,
      )
    );
  };

  <div className=Styles.container>
    <div className=Styles.bookList style={ReactDOMRe.Style.make(~gridAutoColumns="minmax(min-content, max-content)", ())}>
      {books
        |> List.mapi((index, book) =>
          <Book
            key={book.title}
            title={book.title}
            tags={book.tags}
            previewImage={book.previewImage}
            editShipperButton={
              <Button
                onClick={_ => {
                  setEditingShipper(_ => Some(index));
                  toggleEditModal(_ => true);
                }}
                icon=`edit>
                {ReasonReact.string("Edit Shipper")}
              </Button>
            }
          />
          )
      |> Array.of_list
      |> ReasonReact.array}
      <BookForm addBook={book => setBooks(books => [book, ...books])} />
    </div>
    {switch (editingShipperId) {
     | None => ReasonReact.null
     | Some(editingId) =>
       <EditShipperModal
         openModal=openEditModal
         toggleEditModal={state => toggleEditModal(_ => state)}
         resetEditingShipper={_ => setEditingShipper(_ => None)}
         editingShipper={List.nth(shippers, editingId)}
         updateShipper
       />
     }}
  </div>;
};
