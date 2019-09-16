open Ehd;
open Book;

[@react.component]
let make = (~addBook) => {
  let (title, setTitle) = React.useState(() => "");
  let (tags, setTags) = React.useState(() => "");
  let (previewImage, setPreviewImage) = React.useState(() => "");

  <Card>
    <Input
      value=title
      placeholder="Title"
      onChange={e => setTitle(e->ReactEvent.Form.target##value)}
    />
    <Input
      value=previewImage
      placeholder="Image URL"
      onChange={e => setPreviewImage(e->ReactEvent.Form.target##value)}
    />
    <Input
      value=tags
      placeholder="Tags"
      onChange={e => setTags(e->ReactEvent.Form.target##value)}
    />
    <div className=BookStyles.cardFooter>
      <Button
        onClick={_ =>
          addBook(
            title,
            previewImage,
            Js.String.split(",", tags)
            |> Array.to_list
            |> List.map(Js.String.trim),
          )
        }>
        {ReasonReact.string("Add new book")}
      </Button>
    </div>
  </Card>;
};
