# 🖼️ Import Image in Next.js

## 1️⃣ Recommended Way → `next/image`

Next.js provides optimized image component.

```jsx
import Image from "next/image";

<Image src="/images/logo.png" alt="Logo" width={200} height={100} />;
```

✅ Automatic:

- Lazy loading
- Responsive sizing
- Image optimization
- WebP conversion
- Faster performance

👉 **Always prefer this over `<img>` tag**

---

## 2️⃣ Where to Store Images

### ✅ Public Folder (Most Common)

```
public/
   images/
      logo.png
```

Use like : `src = "/images/logo.png";`

- ✔ No import required
- ✔ Best for static assets

---

### ✅ Import From Assets Folder

```
assets/logo.png
```

```jsx
import logo from "@/assets/logo.png";

<Image src={logo} alt="logo" />;
```

Used when:

- image part of component/module
- bundler tracking needed

---

## 3️⃣ External Images (CDN / Firebase Storage)

Add domain in `next.config.js`:

```js
module.exports = {
    images: {
        domains: ["firebasestorage.googleapis.com"],
    },
};
```

Then:

```jsx
<Image src={imageUrl} width={300} height={200} alt="img" />
```

---

## 4️⃣ `<Image>` vs `<img>`

| Feature      | `<img>` | `<Image>` |
| ------------ | ------- | --------- |
| Optimization | ❌      | ✅        |
| Lazy loading | Manual  | Auto      |
| Responsive   | Manual  | Auto      |
| Performance  | Normal  | Optimized |

---

## 5️⃣ Important Rules

- Must provide **width & height** (or `fill`)
- Image paths start from `/public`
- Use `priority` for above-the-fold images
    - Above the fold = image that comes immediately when page loads — without scrolling
    - like Hero banner, product main image, Logo in header
    - Next JS loads this image as early as possible
    - It does not lazy-load it

```jsx
<Image src="/hero.png" priority />
```

---

## ⚡ TL;DR

- Store images → `/public`
- Use → `next/image`
- Configure domains for external images
- Avoid plain `<img>` tag unless necessary

---

## 🖼️ next/image Component — Properties Table

| Property                    | Values (Meaning)                                                                                                    | Example                                   |
| --------------------------- | ------------------------------------------------------------------------------------------------------------------- | ----------------------------------------- |
| **src**                     | `"/image.png"` → from `/public` <br> imported image → local asset <br> external URL → CDN/Firebase image            | `src="/images/logo.png"`                  |
| **alt**                     | `"description"` → accessibility text                                                                                | `alt="Company Logo"`                      |
| **width**                   | number → image width in px                                                                                          | `width={300}`                             |
| **height**                  | number → image height in px                                                                                         | `height={200}`                            |
| **fill**                    | `true` → image fills parent container <br> parent must be `position: relative`                                      | `<Image fill />`                          |
| **sizes**                   | `"100vw"` → full screen <br> responsive breakpoints                                                                 | `sizes="(max-width:768px) 100vw, 50vw"`   |
| **priority**                | `true` → preload important image (hero/banner)                                                                      | `priority`                                |
| **loading**                 | `"lazy"` → load when visible <br> `"eager"` → load immediately                                                      | `loading="lazy"`                          |
| **quality**                 | `1–100` → image compression quality                                                                                 | `quality={80}`                            |
| **className**               | CSS / Tailwind classes                                                                                              | `className="rounded-lg shadow"`           |
| **style**                   | inline CSS object                                                                                                   | `style={{borderRadius:"10px"}}`           |
| **objectFit** _(via style)_ | `"cover"` → fill + crop <br> `"contain"` → full image visible <br> `"fill"` → stretch <br> `"none"` → original size | `style={{objectFit:"cover"}}`             |
| **placeholder**             | `"blur"` → blurred preview <br> `"empty"` → no placeholder                                                          | `placeholder="blur"`                      |
| **blurDataURL**             | base64 image used as blur preview                                                                                   | `blurDataURL="data:image/png;base64,..."` |
| **onLoad**                  | function runs after load                                                                                            | `onLoad={()=>console.log("loaded")}`      |
| **onError**                 | function runs on error                                                                                              | `onError={()=>setError(true)}`            |

## ✅ Most Common Real Usage

```
<Image
  src="/hero.png"
  alt="Hero"
  width={600}
  height={400}
  priority
  className="rounded-lg"
/>
```
