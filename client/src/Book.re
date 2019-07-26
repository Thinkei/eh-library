type book = {
  id: int,
  title: string,
  tags: list(string),
  previewImage: string,
};

module BookStyles = {
  open Css;

  let bookInformationContainer = style([marginLeft(px(10))]);

  let book =
    style([
      display(flexBox),
      margin(px(20)),
      paddingBottom(px(10)),
      borderBottom(px(1), solid, dimgrey),
    ]);

  let title = style([fontWeight(bold)]);

  let tagContainer = style([margin2(~v=px(5), ~h=zero)]);

  let tag =
    style([
      marginRight(px(10)),
      padding(px(2)),
      color(dimgrey),
      fontSize(px(10)),
      border(px(1), solid, dimgrey),
      borderRadius(px(4)),
      display(inlineBlock),
    ]);

  let previewImage = style([maxWidth(px(40))]);

  let editButton =
    style([
      10 |> px |> marginLeft,
      `pointer |> cursor,
      "fff" |> hex |> color,
      "007bff" |> hex |> backgroundColor,
      "007bff" |> hex |> borderColor,
      0.75 |> rem |> borderRadius,
    ]);
};

module Tag = {
  [@react.component]
  let make = (~tag) => {
    <span className=BookStyles.tag> {ReasonReact.string(tag)} </span>;
  };
};
module TagList = {
  [@react.component]
  let make = (~tags) => {
    tags
    |> List.map(tag => <Tag tag key=tag />)
    |> Array.of_list
    |> ReasonReact.array;
  };
};

[@react.component]
let make = (~bookItem, ~setEditingBook) => {
  <div className=BookStyles.book>
    <img
      className=BookStyles.previewImage
      src={bookItem.previewImage}
      alt={bookItem.title}
    />
    <div className=BookStyles.bookInformationContainer>
      <div className=BookStyles.title> {ReasonReact.string(bookItem.title)} </div>
      <div className=BookStyles.tagContainer>
        <TagList tags={bookItem.tags} />
      </div>
    </div>
    <div>
      <button
        className=BookStyles.editButton onClick={_ => setEditingBook(bookItem)}>
        {ReasonReact.string("Edit")}
      </button>
    </div>
  </div>;
};
