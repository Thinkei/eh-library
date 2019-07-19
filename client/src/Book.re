type book = {
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
    tags |> List.map(tag => <Tag tag />) |> Array.of_list |> ReasonReact.array;
  };
};
[@react.component]
let make = (~title, ~tags, ~previewImage) => {
  <div className=BookStyles.book>
    <img className=BookStyles.previewImage src=previewImage alt=title />
    <div className=BookStyles.bookInformationContainer>
      <div className=BookStyles.title> {ReasonReact.string(title)} </div>
      <div className=BookStyles.tagContainer> <TagList tags /> </div>
    </div>
  </div>;
};
