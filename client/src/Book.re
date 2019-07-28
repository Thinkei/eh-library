type book = {
  title: string,
  tags: list(string),
  previewImage: string,
};

open Ehd;

module BookStyles = {
  open Css;

  let bookInformationContainer = style([marginLeft(px(10))]);

  let tagContainer = style([margin2(~v=px(5), ~h=zero)]);

  let previewImage = style([maxHeight(px(180))]);

  let title = style([fontWeight(bold)]);

  let detail = [
    textAlign(`left),
    paddingLeft(px(10)),
  ] |> style

  let cardContent = [
    display(flexBox),
  ] |> style;

  let cardFooter = [
    padding(px(24)),
    textAlign(`right),
    paddingBottom(zero),
    borderTop(px(1), solid, hex("f2f2f2")),
    margin3(~top=px(24), ~h=px(-24), ~bottom=zero),
  ] |> style
};

module Tag = {
  [@react.component]
  let make = (~tag) => {
    <Tag color="volcano"> {ReasonReact.string(tag)} </Tag>;
  };
};
module TagList = {
  [@react.component]
  let make = (~tags) => {
    tags |> List.map(tag => <Tag tag />) |> Array.of_list |> ReasonReact.array;
  };
};
[@react.component]
let make = (~title, ~tags, ~previewImage, ~editShipperButton) => {
  <Card style={ReactDOMRe.Style.make(~paddingBottom="", ())}>
    <div className=BookStyles.cardContent>
      <img className=BookStyles.previewImage src=previewImage alt=title />
      <div className=BookStyles.detail>
        <h4 className=BookStyles.title>{ReasonReact.string(title)}</h4>
        <TagList tags />
      </div>
    </div>
    <div className=BookStyles.cardFooter>
      {editShipperButton}
    </div>
  </Card>
};
